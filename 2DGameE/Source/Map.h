#pragma once
#include "Game.h"
#include <vector>
#include "Vector2D.h"


class ColliderComponentBase;

class Map {
public:
	Map(Game * mGame);
	~Map();

	/* Loads map by loading .map file ans map assets file .masset.
	 * It also clear old map variables
	 * @param mapRawPath should be raw map path. eg: map  (not map.map) */
	void LoadMap(const char * mapRawPath);

	/* Loads .map file
	 * @param mapPath should be valid map file (map.map) */
	void LoadMapFromFile(const char * mapPath);

	/* Loads .masset file
	 * @param mapPath should be valid map assets file (map.masset) */
	void LoadMapAssetsFromFile(const char * mapPath);

	/* Sets map variable with given @param newMap
	 * @param newMap should be valid std::vector<std::vector<int>>  */
	void SetMap(std::vector<std::vector<int>> newMap);

	/* Returns map width in px. */
	int GetMapWidth();

	/* Returns map height in px. */
	int GetMapHeight();

	/* Check if map at x and y is colliding.
	 * @param checkBounds - Check if x and y are in map bounds. */
	int GetMapCollision(int x, int y, bool checkBounds);

	/* Draws map called every frame in main loop. (render function) */
	void DrawMap();

	/* Used to get array ids of map grid for collision. */
	Vector2D<int> GetMapGridAtPosition(int x, int y);


	/* Adds dynamic collider to dynamic colliders vector. */
	void AddCollider(ColliderComponentBase * collider);

	/* Removes dynamic collider from dynamic colliders vector. */
	void RemoveCollider(ColliderComponentBase * collider);

	/* Adds dynamic collider to dynamic colliders vector. */
	void AddColliderToGrid(ColliderComponentBase * collider);

	/* Removes dynamic collider from dynamic colliders vector. */
	void RemoveColliderFromGrid(ColliderComponentBase * collider);

	/* Updates collision
	 * https://gamedev.stackexchange.com/questions/39931/fast-accurate-2d-collision */
	void updateCollision();

protected:
	/* Creates collision based on map. Don't call this function without reason.
	 * It's called when map is created */
	void SetupCollision();

private:
	std::string mapSuffix = ".map";
	std::string mapAssetsSuffix = ".masset";

	SDL_Rect src, dest;

	Game * game;

	// Map textures
	std::vector<std::vector<int>> map;
	std::vector<SDL_Texture*> textures;
	std::vector<bool> textureCollisions;

	// Collision 
	std::vector<ColliderComponentBase*> colliders;

	std::vector<std::vector<std::vector<ColliderComponentBase*>>> collidersMap;

};