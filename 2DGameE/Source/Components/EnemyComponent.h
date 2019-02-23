#pragma once
#include "ECS.h"
#include "../AI.h"


class SimplePhysicsComponent;

class EnemyComponent : public AI
{
public:
	EnemyComponent();
	~EnemyComponent();

	virtual void init() override;
	//virtual void postInit() override;
	//virtual void update() override;
	//virtual void render() override;

protected:
	SimplePhysicsComponent * physics;

};

