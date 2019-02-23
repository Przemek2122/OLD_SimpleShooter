#include "TransparentColliderComponent.h"



TransparentColliderComponent::TransparentColliderComponent(std::string colliderTag) : ColliderComponentBase(colliderTag)
{
	colliderType = COLLIDER_TRANSPARENT;
}


TransparentColliderComponent::~TransparentColliderComponent()
{
}
