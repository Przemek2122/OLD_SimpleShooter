#include "AssetsManager.h"
#include "Util.h"

AssetsManager::AssetsManager(Manager* man) : manager(man)
{}

AssetsManager::~AssetsManager()
{}

Texture * AssetsManager::addTexture(std::string id, const char* path)
{
	// Create new texture
	numOfTextures++;
	Texture * newTexture = new Texture(TextureManager::LoadTexture(path), path, numOfTextures);

	// Add to vector
	textures.emplace(id, newTexture);

	return newTexture;
}

Texture * AssetsManager::addCustomTexture(std::string id, SDL_Texture * tex, const char* path)
{
	// Create new texture
	numOfTextures++;
	Texture * newTexture = new Texture(tex, path, numOfTextures);

	// Add to vector
	textures.emplace(id, newTexture);

	return newTexture;
}

bool AssetsManager::hasTexture(std::string id)
{
	if (textures.count(id))
		return true;

	return false;
}

Texture * AssetsManager::ensureTexture(std::string id, const char * path)
{
	if (hasTexture(id))
	{
		getTexture(id);
	}
	else
	{
		return addTexture(id, path);
	}
}

Texture * AssetsManager::getTexture(std::string id)
{
	return textures[id];
}

SDL_Texture * AssetsManager::getRawTexture(std::string id)
{
	return textures[id]->texture;
}

void AssetsManager::addFont(std::string id, std::string path, int fontSize)
{
	TTF_Font *font = TTF_OpenFont(path.c_str(), fontSize);
	if (!font) {
		Util::Error("Font not loaded! TTF_OpenFont: \n");
		Util::Error(TTF_GetError());
	}
	else
		fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font* AssetsManager::getFont(std::string id)
{
	return fonts[id];
}
