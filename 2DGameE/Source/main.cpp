#include "Util.h"

#include "game.h"
Game *game = nullptr;

bool FPSLimitEnabled = true;

int main(/*int argc, char * argv[]*/){
	// FPS limit
	const int FPS = 60;
	const float frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	// Deltatime
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;

	game = new Game();
	game->init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (game->isRunning()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		if (FPSLimitEnabled == true) {
			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime) {
				SDL_Delay(frameDelay - frameTime);
			}
		}

		// Deltatime
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		game->setDeltaTime((double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency()));
	}

	game->clean();

	return 0;
}