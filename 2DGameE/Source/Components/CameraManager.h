#pragma once
#include "ECS.h"
#include "../Vector2D.h"

class TransformComponent;
class Game;

class CameraManagerComponent : public Component
{
public:
	float MaxAcceleration = 100;
	float Speed = 7.0f;

	CameraManagerComponent();
	~CameraManagerComponent();

	void init() override;
	void update() override;

	void setCameraPosition(Vector2D<> pos);
	Vector2D<> getCameraPosition();

private:
	bool keepCameraInBounds = true;

	Game * game;
	TransformComponent * transform;

};

