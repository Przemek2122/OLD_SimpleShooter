#include "AI.h"
#include "EngineMath.h"
#include "game.h"
#include "Components/CameraManager.h"
#include "Components/TransformComponent.h"


AI::AI() {}

AI::~AI() {}

void AI::updatePlayerDistance()
{
	playerDistance = EMath::Distance2D(entity->getManager().game->player->getComponent<TransformComponent>().Location, 
		entity->getComponent<TransformComponent>().Location);
}

void AI::updateRotationToPlayer()
{
	Vector2D<float> tempPos = entity->getComponent<TransformComponent>().Location;
	Vector2D<float> camPos = entity->getManager().game->camera->getComponent<CameraManagerComponent>().getCameraPosition();
	Vector2D<float> entityPos = entity->getComponent<TransformComponent>().Location;
	//double rad = EMath::Get2DAngleOfPointRadians(Vector2D<float>(16, 16) + (tempPos.Add(camPos)), entityPos) + M_PI;
	double rad = EMath::Get2DAngleOfPointRadians(Vector2D<float>(16, 16) + tempPos + camPos, entityPos) + M_PI;
}

