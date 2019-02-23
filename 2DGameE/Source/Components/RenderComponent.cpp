#include "RenderComponent.h"
#include "../TextureManager.h"
#include "../AssetsManager.h"
#include "TransformComponent.h"
#include "CameraManager.h"


void RenderComponent::LoadTexture(const char* texturesheet) {
	Texture = TextureManager::LoadTexture(texturesheet);
}

/* Uses texture from asset manager */
void  RenderComponent::UseTexture(const char* textureID) {
	Texture = entity->getManager().game->assets->getRawTexture(textureID);
}

void  RenderComponent::init()
{
	transform = &entity->EnsureComponent<TransformComponent>();
}

void  RenderComponent::render()
{
	// Prepare
	srcRect = transform->Rect;

	destRect.x = transform->Location.X + entity->getManager().game->camera->getComponent<CameraManagerComponent>().getCameraPosition().X;
	destRect.y = transform->Location.Y + entity->getManager().game->camera->getComponent<CameraManagerComponent>().getCameraPosition().Y;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	// Render
	SDL_RenderCopyEx(Game::renderer, Texture, &srcRect, &destRect, transform->Rotation, &center, flip);
}