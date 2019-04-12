#pragma once
#include "ColliderComponentBase.h"
#include "SDL.h"


class TransformComponent;

class RectColliderComponent : public ColliderComponentBase
{
public:
	RectColliderComponent(std::string colliderTag);
	Vector2D<int> vertex_TL; // Top left vertex
	Vector2D<int> vertex_TR; // Top right vertex
	Vector2D<int> vertex_BL; // Bottom left vertex
	Vector2D<int> vertex_BR; // Bottom right vertex

#ifdef _DEBUG
	SDL_Color colliderColor = { 245, 215, 65, 0 };
	bool drawDebugCollider = true;
#endif

	SDL_Rect inline getRect();

	Vector2D<int> getCenter();

	void customUpdate() override;
	void customRender() override;

private:
	bool moving = true;

};
