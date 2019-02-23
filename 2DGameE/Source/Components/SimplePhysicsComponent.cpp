#include "SimplePhysicsComponent.h"
#include <assert.h>
#include "ECS.h"
#include "TransformComponent.h"
#include "../Util.h"
#include "../game.h"
#include "../map.h"
#include "../EngineMath.h"


SimplePhysicsComponent::SimplePhysicsComponent()
{}

SimplePhysicsComponent::~SimplePhysicsComponent()
{}

void SimplePhysicsComponent::init()
{
	transform = &entity->EnsureComponent<TransformComponent>();

	tMap = entity->getManager().game->map;
}

void SimplePhysicsComponent::update()
{
	double delta = entity->getManager().game->getDeltaTime();

	if (anyMovement())
	{
		// Movement damping
		if (roundf(movementAcceleration.X) != 0)
			movementAcceleration.X -= movementAcceleration.X * movementDamping * delta;
		else
			movementAcceleration.X = 0;

		if (roundf(movementAcceleration.Y) != 0)
			movementAcceleration.Y -= movementAcceleration.Y * movementDamping * delta;
		else
			movementAcceleration.Y = 0;

		// Rotation damping
		if (rotationAcceleration > 0)
			rotationAcceleration -= rotationAcceleration * rotationDamping * delta;
		else
			rotationAcceleration += rotationAcceleration * rotationDamping * delta;

		// Update Location
		transform->Location.X += movementAcceleration.X * delta;
		transform->Location.Y += movementAcceleration.Y * delta;

		// Update rotation
		transform->Rotation += rotationAcceleration;


		// Keep entity in map, don't allow to go outside
		if (keepEntityInMapBounds)
		{
			mapBounds = Vector2D<>(entity->getManager().game->map->GetMapWidth(), entity->getManager().game->map->GetMapHeight());
			outOfBounds = false;

			// left
			if (transform->Location.X <= 0)
			{
				transform->Location.X = 0;
				outOfBounds = true;
			}
			// right
			else if (transform->Location.X > mapBounds.X - 32)
			{
				transform->Location.X = mapBounds.X - 33;
				outOfBounds = true;
			}
			// top
			if (transform->Location.Y <= 0)
			{
				transform->Location.Y = 0;
				outOfBounds = true;
			}
			// bottom
			else if (transform->Location.Y > mapBounds.Y - 32)
			{
				transform->Location.Y = mapBounds.Y - 33;
				outOfBounds = true;
			}

			// Check for collision, should be after checking if in MapBounds
			if (!outOfBounds) // Handle collision
			{
				if (coll = tMap->GetMapCollision(transform->Location.X, transform->Location.Y, false) != 0)
				{
					Util::Debug(std::to_string(coll));

					if (!bouncing)
					{
						bounce();
						bouncing = true;
					}
				}
			}
		}

		if (coll == 0 && bouncing)
		{
			bouncing = false;
		}
	}
}

Vector2D<> SimplePhysicsComponent::getMovementAcceleration()
{
	return movementAcceleration;
}

void SimplePhysicsComponent::addMovementAcceleration(Vector2D<> acceleration)
{
	// Check if it doesn't exceed the limit
	if (movementAcceleration.X > maxAcceleration || movementAcceleration.X < -maxAcceleration)
		acceleration.X = 0;
	if (movementAcceleration.Y > maxAcceleration || movementAcceleration.Y < -maxAcceleration)
		acceleration.Y = 0;

	movementAcceleration += acceleration;
}

float SimplePhysicsComponent::getRotationAcceleration()
{
	return rotationAcceleration;
}

void SimplePhysicsComponent::addRotationAcceleration(float acceleration)
{
	rotationAcceleration += acceleration;
}

void SimplePhysicsComponent::setMovementDamping(float damping)
{
	movementDamping = damping;
}

void SimplePhysicsComponent::setRotationDamping(float damping)
{
	rotationDamping = damping;
}

void SimplePhysicsComponent::stop()
{
	movementAcceleration = Vector2D<>(0, 0);
	rotationAcceleration = 0;
}

void SimplePhysicsComponent::bounce()
{
	movementAcceleration.X = movementDamping * 0.1f * -movementAcceleration.X + -movementAcceleration.X;
	movementAcceleration.Y = movementDamping * 0.1f * -movementAcceleration.Y + -movementAcceleration.Y;
}

bool SimplePhysicsComponent::anyMovement()
{
	if (movementAcceleration.X == 0 && movementAcceleration.Y == 0)
		return false;
	else
		return true;
}
