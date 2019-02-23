#pragma once
#include "ECS.h"
#include "SDL.h"
#include "../Vector2D.h"


enum ColliderType
{
	/* Base collider */
	COLLIDER_BASE = 0,
	/* Transparent collider is hitting object. It can't be hit. */
	COLLIDER_TRANSPARENT = 1,
	/* Rectangle collider */
	COLLIDER_RECT = 2,
	/* Circle collider */
	COLLIDER_CIRCLE = 3
};

class TransformComponent;
class Map;

class ColliderComponentBase : public Component
{
public:
	std::string tag = "none";
	ColliderType colliderType = COLLIDER_BASE;
	TransformComponent* transform;
	Map * map;

	Vector2D<int> gridPositions[4];
	std::vector<ColliderComponentBase*> otherColliders;

	bool colliding = false;
	bool isMoving = true;
	bool storeReferences; // if true references of other colliding object will be in otherColliders vector

	ColliderComponentBase();
	ColliderComponentBase(std::string colliderTag);
	~ColliderComponentBase();

	void init() override;
	void update() override;
	void render() override;

	virtual void customInit(){}
	virtual void customUpdate(){}
	virtual void customRender(){}

};

