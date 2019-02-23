#pragma once
#include "ECS.h"
#include "SDL.h"
#include "../Vector2D.h"


class TransformComponent;

class RenderComponent : public Component {
public:
	TransformComponent* transform;

	SDL_Texture* Texture;
	SDL_Rect srcRect = {32, 32, 0, 0}, destRect;
	SDL_Point center;
	SDL_RendererFlip flip;

	/* Use new texture - Use UseTexture() instead wheather possible */
	void LoadTexture(const char* texturesheet);

	/* Uses texture from asset manager */
	void UseTexture(const char* textureID);
		
	void init() override;
	void render() override;

};