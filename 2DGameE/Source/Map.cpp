#include "Map.h"
#include <algorithm>
#include "TextureManager.h"
#include "Util.h"
#include <fstream>
#include "Components/CameraManager.h"
#include "EngineMath.h"
#include "Components/ColliderComponentBase.h"
#include "Components/RectColliderComponent.h"
#include "Components/TransformComponent.h"
#include "DynamicCollision.h"


Map::Map(Game * mGame)
{
	game = mGame;

	LoadMap("assets/maps/map");

	src.x = src.y = 0;
	src.w = dest.w = 32;
	src.h = dest.h = 32;

	dest.x = dest.y = 0;
}

Map::~Map(){}

void Map::LoadMap(const char * mapPath)
{
	// Clear old variables (if used)
	map.clear();
	for (int i = 0; i < textures.size(); i++)
		SDL_free(textures[i]);
	textures.clear();
	textureCollisions.clear();

	std::string path = mapPath + mapSuffix;
	LoadMapFromFile(path.c_str());

	path = mapPath + mapAssetsSuffix;
	LoadMapAssetsFromFile(path.c_str());
}

void Map::LoadMapFromFile(const char * mapPath)
{
	std::vector<std::vector<int>> newMap;

	Util::Info("Loading map from: " + (std::string)mapPath);

	std::filebuf file;
	if (file.open(mapPath, std::ios::in)) 
	{
		std::istream is(&file);
		std::string s;
		while (std::getline(is, s))
		{
			std::vector <int> temp;

			for (int i = 0; i < s.size(); i++)
			{
				if (s[i] != ' ' && s[i] != ',')
					temp.emplace_back(s[i] - '0');
			}

			newMap.emplace_back(temp);
		}

		// set loaded map
		map = newMap;

		// prepare collision
		SetupCollision();
	}
	else
	{
		Util::Error("Can't load map (problem with file) from: " + (std::string)mapPath);
	}
}

void Map::LoadMapAssetsFromFile(const char * mapPath)
{
	Util::Info("Loading map assets from: " + (std::string)mapPath);

	std::filebuf file;
	if (file.open(mapPath, std::ios::in))
	{
		std::istream is(&file);
		std::string s;
		while (std::getline(is, s))
		{
			std::string texturePath = "";

			bool start = false; int num = 0;
			for (int i = 1; i < s.size(); i++)
			{
				if (start) 
				{
					texturePath += s.at(i);
				}

				if (num == 1 && !start)
				{
					if (s[i] == '0' || s[i] == '1')
					{
						if (s[i] == '0')
							textureCollisions.push_back(false);
						else
							textureCollisions.push_back(true);

						start = true;
						i += 2;
					}
				}

				// if after , (to do not add id to path)
				if (s[i] == ',')
				{
					num++;
				}
			}

			textures.push_back(TextureManager::LoadTexture(texturePath.c_str()));
		}
	}
	else
	{
		Util::Error("Can't load map assets (problem with file) from: " + (std::string)mapPath);
	}
}

void Map::SetMap(std::vector<std::vector<int>> newMap) {
	map = newMap;
}

int Map::GetMapWidth()
{
	return map[0].size() * 32;
}

int Map::GetMapHeight()
{
	return map.size() * 32;
}

int Map::GetMapCollision(int x, int y, bool checkBounds)
{
	if (checkBounds)
		if (x <= 0 || x > GetMapWidth() || y <= 0 || y > GetMapHeight())
			return 0;

	int nx = x / 32;
	int ny = y / 32;

	if (textureCollisions[map[ny][nx]])
		return 1;

	nx = (x + 32) / 32;
	ny = y / 32;

	if (textureCollisions[map[ny][nx]])
		return 2;

	nx = x / 32;
	ny = (y + 32) / 32;

	if (textureCollisions[map[ny][nx]])
		return 3;

	nx = (x + 32) / 32;
	ny = (y + 32) / 32;

	if (textureCollisions[map[ny][nx]])
		return 4;

	return 0;
}

void Map::DrawMap()
{
	int type = 0;

	for (int row = 0; row < map.size(); row++) {
		for (int column = 0; column < map[0].size(); column++) {
			type = map[row][column];

			dest.x = column * 32 + game->camera->getComponent<CameraManagerComponent>().getCameraPosition().X;
			dest.y = row * 32 + game->camera->getComponent<CameraManagerComponent>().getCameraPosition().Y;

			TextureManager::Draw(textures[type], src, dest);
		}
	}
}

Vector2D<int> Map::GetMapGridAtPosition(int x, int y)
{
	return Vector2D<int>(floorf(x / 32), floorf(y / 32));
}

void Map::AddCollider(ColliderComponentBase * collider)
{
	colliders.emplace_back(collider);
	AddColliderToGrid(collider);
}

void Map::RemoveCollider(ColliderComponentBase * collider)
{
	colliders.erase(std::remove(colliders.begin(), colliders.end(), collider), colliders.end());
	RemoveColliderFromGrid(collider);
}

void Map::AddColliderToGrid(ColliderComponentBase * collider)
{
	TransformComponent * transformComp = collider->transform;
	// Left top 
	collider->gridPositions[0] = GetMapGridAtPosition(transformComp->Location.X, transformComp->Location.Y);
	// Right top
	collider->gridPositions[1] = GetMapGridAtPosition(transformComp->Location.X + transformComp->Rect.w, transformComp->Location.Y);
	// Left bottom
	collider->gridPositions[2] = GetMapGridAtPosition(transformComp->Location.X, transformComp->Location.Y + transformComp->Rect.h);
	// Right bottom
	collider->gridPositions[3] = GetMapGridAtPosition(transformComp->Location.X + transformComp->Rect.w, transformComp->Location.Y + transformComp->Rect.h);

	for (int i = 0; i < 4; i++)
	{
		// If not last and collider doesn't stay on same gris place (1 spot instead of casual 4)
		if (i != 3 && collider->gridPositions[i] != collider->gridPositions[i + 1])
		{
			collidersMap[collider->gridPositions[i].Y][collider->gridPositions[i].X].emplace_back(collider);
		}
		else
		{
			collidersMap[collider->gridPositions[i].Y][collider->gridPositions[i].X].emplace_back(collider);
		}
	}
}

void Map::RemoveColliderFromGrid(ColliderComponentBase * collider)
{
	for (int i = 0; i < 4; i++)
	{
		// If not last and collider doesn't stay on same gris place (1 spot instead of casual 4)
		if (i != 3 && collider->gridPositions[i] != collider->gridPositions[i + 1])
		{
			collidersMap[collider->gridPositions[i].Y][collider->gridPositions[i].X].
				erase(std::remove(collidersMap[collider->gridPositions[i].Y][collider->gridPositions[i].X].begin(),
					collidersMap[collider->gridPositions[i].Y][collider->gridPositions[i].X].end(), collider),
					collidersMap[collider->gridPositions[i].Y][collider->gridPositions[i].X].end());
		}
		else
		{
			collidersMap[collider->gridPositions[i].Y][collider->gridPositions[i].X].
				erase(std::remove(collidersMap[collider->gridPositions[i].Y][collider->gridPositions[i].X].begin(),
					collidersMap[collider->gridPositions[i].Y][collider->gridPositions[i].X].end(), collider),
					collidersMap[collider->gridPositions[i].Y][collider->gridPositions[i].X].end());
		}
	}
}



void Map::updateCollision()
{
	std::string tag1 = "1", tag2 = "2";

	for (int y = 0; y < collidersMap.size(); y++) // Map coordinate Y
	{
		for (int x = 0; x < collidersMap[y].size(); x++) // Map coordinate X
		{
			for (int i = 0; i < collidersMap[y][x].size(); i++) // Collider
			{
				collidersMap[y][x][i]->colliding = false;

				if (tag1 != tag2 && collidersMap[y][x].size() > 1) // if there is more then one collider
				{
					if (i + 1 < collidersMap[y][x].size())
					{
						if (collidersMap[y][x][i]->storeReferences && collidersMap[x][y][i]->otherColliders.size() > 0)
							collidersMap[y][x][i]->otherColliders.clear();

						if (Collision::rectangleCollision(static_cast<RectColliderComponent*>(collidersMap[y][x][i])->getRect(),
							static_cast<RectColliderComponent*>(collidersMap[y][x][i + 1])->getRect()) != 0)
						{
							Util::Debug("Colliders are certainly touching.");

							collidersMap[y][x][i]->colliding = true;

							// This collider
							if (collidersMap[y][x][i]->storeReferences)
							{
								collidersMap[y][x][i + 1]->otherColliders.emplace_back(collidersMap[y][x][i]);
							}

							// Other collider
							if (collidersMap[y][x][i + 1]->storeReferences)
							{
								collidersMap[y][x][i]->otherColliders.emplace_back(collidersMap[y][x][i + 1]);
							}

							tag1 = collidersMap[y][x][i]->tag;
							tag2 = collidersMap[y][x][i + 1]->tag;
						}
					}
				}
			}
		}
	}
}

void Map::SetupCollision()
{
	Util::Info("Generating collision...");

	if (collidersMap.size() > 0)
		collidersMap.clear();

	for (int y = 0; y < map.size(); y++)
	{
		std::vector<std::vector<ColliderComponentBase*>> temp;

		for (int x = 0; x < map[y].size(); x++)
		{
			std::vector<ColliderComponentBase*> temp2;
			temp.emplace_back(temp2);
		}

		collidersMap.emplace_back(temp);
	}
}
