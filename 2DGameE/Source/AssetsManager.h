#pragma once

#include <map>
#include "SDL_ttf.h"
#include "Components/ECS.h"
#include "Vector2D.h"
#include "TextureManager.h"

class AssetsManager{
public:
	AssetsManager(Manager* man);
	~AssetsManager();

	/* Adds texture to map. (as many times as called) */
	Texture * addTexture(std::string id, const char* path);
	/* Adds texture (specified with parameter SDL_Texture * tex) to map */
	Texture * addCustomTexture(std::string id, SDL_Texture * tex, const char* path = "Custom");
	/* Returns true if texture with id found or false otherwise. */
	bool hasTexture(std::string id);
	/* Creates new texture if id doesn't exists. */
	Texture * ensureTexture(std::string id, const char* path);
	/* Returns texture by id. */
	Texture * getTexture(std::string id);
	/* Returns raw pointer to SDL_Texture. */
	SDL_Texture * getRawTexture(std::string id);

	/* Adds new font to map. */
	void addFont(std::string id, std::string path, int fontSize);
	/* Returns font from map. */
	TTF_Font* getFont(std::string id);

private:
	Manager * manager;
	long int numOfTextures = 0;
	std::map<std::string, Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;

};