#include "CameraManager.h"
#include "../Game.h"
#include "../Keyboard.h"
#include "TransformComponent.h"
#include "../Map.h"
#include "../UI/UI.h"


CameraManagerComponent::CameraManagerComponent() {}

CameraManagerComponent::~CameraManagerComponent() {}

void CameraManagerComponent::init()
{
	transform = &entity->EnsureComponent<TransformComponent>();
	game = entity->getManager().game;
}

void CameraManagerComponent::update()
{
	Vector2D<> loc = game->player->getComponent<TransformComponent>().Location;
	Vector2D<> halfScreen = Vector2D<>(UIUtil::getScreenPercentW(50) - 32, UIUtil::getScreenPercentH(50) - 32);
	Vector2D<> newLocation = Vector2D<>(-loc.X + halfScreen.X, -loc.Y + halfScreen.Y);

	// Keep kamera in map, don't allow to go outside
	if (keepCameraInBounds)
	{
		Vector2D<> mapBounds = Vector2D<>(game->map->GetMapWidth(), game->map->GetMapHeight());

		// left
		if (loc.X < halfScreen.X)
			newLocation.X = 0;

		// right
		else if (loc.X > mapBounds.X - UIUtil::getScreenPercentW(50) - 32)
			newLocation.X = -mapBounds.X + UIUtil::getScreenPercentW(100);

		// top
		if (loc.Y < halfScreen.Y)
			newLocation.Y = 0;

		// bottom
		else if (loc.Y > mapBounds.Y - UIUtil::getScreenPercentH(50) - 32)
			newLocation.Y = -mapBounds.Y + UIUtil::getScreenPercentH(100);
	}

	transform->Location = newLocation;
}

void CameraManagerComponent::setCameraPosition(Vector2D<> pos)
{
	transform->Location = pos;
}

Vector2D<> CameraManagerComponent::getCameraPosition()
{
	return transform->Location;
}
