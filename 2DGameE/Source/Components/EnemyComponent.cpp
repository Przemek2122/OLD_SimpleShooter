#include "EnemyComponent.h"
#include "../EngineMath.h"
#include "RectColliderComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "SimplePhysicsComponent.h"


EnemyComponent::EnemyComponent() {}

EnemyComponent::~EnemyComponent() {}


void EnemyComponent::init()
{
	entity->EnsureComponent<TransformComponent>().Location = Vector2D<>(100, 100);

	entity->EnsureComponent<RenderComponent>().LoadTexture("assets/characters/head_enemy_2.png");

	physics = &entity->EnsureComponent<SimplePhysicsComponent>();

	entity->EnsureComponent<RectColliderComponent>("Enemy");
}

