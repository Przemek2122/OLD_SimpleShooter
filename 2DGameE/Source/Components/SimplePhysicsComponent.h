#pragma once
#include "ECS.h"
#include "../Vector2D.h"

class TransformComponent;
class Map;

class SimplePhysicsComponent : public Component
{
public:
	SimplePhysicsComponent();
	~SimplePhysicsComponent();

	void init() override;
	void update() override;

	Vector2D<> getMovementAcceleration();
	void addMovementAcceleration(Vector2D<> acceleration);
	float getRotationAcceleration();
	void addRotationAcceleration(float acceleration);

	void setMovementDamping(float damping);
	void setRotationDamping(float damping);

	void stop();

	virtual void bounce();

protected:
	bool anyMovement();

protected:
	Vector2D<> movementAcceleration = Vector2D<>(0, 0);
	float rotationAcceleration = 0;
	float movementDamping = 0.3f;
	float rotationDamping = 0.1f;
	float maxAcceleration = 100;
	bool keepEntityInMapBounds = true;
	bool isMoving = false;

	Vector2D<> mapBounds;
	bool outOfBounds;
	bool bouncing;
	int coll = 0;

	TransformComponent* transform;
	Map * tMap;

};

