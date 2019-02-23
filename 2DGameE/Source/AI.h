#pragma once
#include "Components/ECS.h"



class AI : public Component
{
public:
	AI();
	~AI();

	void updatePlayerDistance();
	void updateRotationToPlayer();

protected:
	float playerDistance = 0;

};

