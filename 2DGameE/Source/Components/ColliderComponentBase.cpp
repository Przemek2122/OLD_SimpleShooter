#include "ColliderComponentBase.h"
#include "TransformComponent.h"
#include "../Map.h"
#include "../game.h"
#include "CameraManager.h"


ColliderComponentBase::ColliderComponentBase(std::string colliderTag)
{
	tag = colliderTag;
}

ColliderComponentBase::ColliderComponentBase()
{
	tag = "Col_" + entity->getEntityID();
}

ColliderComponentBase::~ColliderComponentBase()
{
	map->RemoveCollider(this);
}

void ColliderComponentBase::init()
{
	map = entity->getManager().game->map;

	transform = &entity->EnsureComponent<TransformComponent>();
	map->AddCollider(this);

	customInit();
}

void ColliderComponentBase::update()
{
	if (isMoving)
	{
		map->RemoveColliderFromGrid(this);
		map->AddColliderToGrid(this);
	}

	customUpdate();
}



void ColliderComponentBase::render()
{
	customRender();
}
