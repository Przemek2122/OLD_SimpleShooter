#pragma once
#include "ECS.h"
#include "TransformComponent.h"
class ProjectileComponent : public Component
{
public:
	ProjectileComponent();
	~ProjectileComponent();

	void init() override;

	void SetProjectile(double rad, int mRange, int mSpeed);

	void update() override;

private:
	TransformComponent* transform;
	Vector2D<> start;
	Vector2D<> velocity = Vector2D<>(0, 0);
	double radians;
	int range = 0;
	int speed = 0;
	double distance = 0;

};

