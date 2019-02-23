#include "ECS.h"
#include "TransformComponent.h"
#include "../game.h"
#include "CameraManager.h"



void TransformComponent::setTransform(int x, int y)
{
	Location.X = x;
	Location.Y = y;
}

Vector2D<> TransformComponent::getWorldLocation()
{
	return Location + entity->getManager().game->camera->getComponent<CameraManagerComponent>().getCameraPosition();
}

Vector2D<> TransformComponent::getLocation()
{
	return Location;
}
