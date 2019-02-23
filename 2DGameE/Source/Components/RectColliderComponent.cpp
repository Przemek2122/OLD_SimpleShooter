#include "RectColliderComponent.h"
#include "TransformComponent.h"
#include "CameraManager.h"
#include "../game.h"
#include "../Map.h"
#include "../EngineMath.h"
#include "../CustomShapes.h"


RectColliderComponent::RectColliderComponent(std::string colliderTag) : ColliderComponentBase(colliderTag) 
{
	colliderType = COLLIDER_RECT;
}

SDL_Rect RectColliderComponent::getRect()
{
	SDL_Rect newRect = transform->Rect;

	newRect.x += transform->Location.X;
	newRect.y += transform->Location.Y;

	return newRect;
}

void RectColliderComponent::customUpdate()
{
	Vector2D<int> * vertices = EMath::RotateRect(getRect(), EMath::GetRectCenter(getRect()), EMath::DegreesToRadians(45));

	//Util::Debug(vertices[0]);
	//Util::Debug(vertices[0] + transform->Location);

	vertex_TL = vertices[0];
	vertex_TR = vertices[1];
	vertex_BL = vertices[2];
	vertex_BR = vertices[3];
}

void RectColliderComponent::customRender()
{
#ifdef _DEBUG
	if (drawDebugCollider)
	{
		Vector2D<> camLoc = entity->getManager().game->camera->getComponent<CameraManagerComponent>().getCameraPosition();

		SDL_SetRenderDrawColor(Game::renderer, colliderColor.r, colliderColor.g, colliderColor.b, colliderColor.a);

		// Debug collider
		SDL_RenderDrawLine(Game::renderer, vertex_TL.X, vertex_TL.Y, vertex_TR.X, vertex_TR.Y);
		SDL_RenderDrawLine(Game::renderer, vertex_TR.X, vertex_TR.Y, vertex_BR.X, vertex_BR.Y);
		SDL_RenderDrawLine(Game::renderer, vertex_BR.X, vertex_BR.Y, vertex_BL.X, vertex_BL.Y);
		SDL_RenderDrawLine(Game::renderer, vertex_BL.X, vertex_BL.Y, vertex_TL.X, vertex_TL.Y);

		// Center of collider
		Vector2D<int> center = EMath::GetRectCenter(getRect()) + camLoc;
		SDL_RenderDrawPoint(Game::renderer, center.X, center.Y);
		Shapes::drawCircle(Game::renderer, center.X, center.Y, 2);
	}
#endif
}
