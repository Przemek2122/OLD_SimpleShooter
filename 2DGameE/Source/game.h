#pragma once

#include "SDL.h"
#undef main

#include "SDL_image.h"
#include "SDL_ttf.h"


class SocketsManager;
class Manager;
class Entity;
class AssetsManager;
class AudioManager;
class UIManager;
class Map;

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool isRunning(){ return running; }

	void setDeltaTime(double time);
	double getDeltaTime();


	static SDL_Window * window;
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static AssetsManager* assets;

	SocketsManager * sockets;
	Manager * ECSManager;
	UIManager * UiManager;
	AudioManager * audioManager;
	Map* map;

	bool server;

	Entity * camera;
	Entity * player;

private:
	bool checkFPS = true;
	time_t time1;
	double deltaTime = 0;

	int cnt = 0;
	bool running;

};