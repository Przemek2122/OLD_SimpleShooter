#pragma once
#include "game.h"


class TextureManager {
public:
	TextureManager();
	~TextureManager();

	/* Loads texture even if already loaded. Will load as many times as it's called. */ 
	static SDL_Texture* LoadTexture(const char* filename);

	/* Use to draw texture. */
	static void Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest);

};

class Texture {
public:
	SDL_Texture * texture;
	const char* filename;
	long int textureID;

	Texture(SDL_Texture * mTexture, const char* mFilename, long int mTextureID) : texture(mTexture), filename(mFilename), textureID(mTextureID)
	{
		
	}

	~Texture() 
	{
		SDL_DestroyTexture(texture);
	}
};