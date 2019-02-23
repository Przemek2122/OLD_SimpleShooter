#include <iostream>
#include "TextureManager.h"
#include "Util.h"

TextureManager::TextureManager()
{}

TextureManager::~TextureManager()
{}

SDL_Texture* TextureManager::LoadTexture(const char* texturePath)
{
	// Attempt load
	SDL_Surface* tmpSurface = IMG_Load(texturePath);

	// Check if succesfuly loaded
	if (!tmpSurface)
		Util::Error((std::string)SDL_GetError() + "Can't load texture, base path: " + (std::string)SDL_GetBasePath());
	else
		Util::Info("Loaded: " + (std::string)texturePath);

	// To memory
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest) 
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}