#include "ProjectileComponent.h"
#include "../Util.h"
#include "../game.h"
#include "../EngineMath.h"


ProjectileComponent::ProjectileComponent(){}

ProjectileComponent::~ProjectileComponent(){}

void ProjectileComponent::init()
{
	transform = &entity->getComponent<TransformComponent>();
}

void ProjectileComponent::SetProjectile(double rad, int mRange, int mSpeed)
{
	start = transform->Location;
	radians = rad + 0.05;
	transform->Rotation = EMath::RadiansToDegrees(rad) + 90;
	range = mRange;
	speed = mSpeed;
}

void ProjectileComponent::update()
{
	transform->Location.X += cos(radians) * speed * entity->getManager().game->getDeltaTime();
	transform->Location.Y += sin(radians) * speed * entity->getManager().game->getDeltaTime();

	distance = EMath::Distance2D(start, transform->Location);

	if (distance > range)
	{
		//std::cout << "Out of Range" << std::endl;
		entity->destroy();
	}
}
