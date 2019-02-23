#pragma once
#include "Components/CameraManager.h"

void Game::handleEvents()
{
	while (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_MOUSEMOTION: // Mouse movement X & Y
			Mouse::SetMouse(event.motion.x, event.motion.y);
			break;

		case SDL_MOUSEBUTTONDOWN: // Press Mouse
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				Mouse::SetLMB(true);
				break;
			case SDL_BUTTON_RIGHT:
				Mouse::SetRMB(true);
				break;

			default:
				break;
			}
			break;

		case SDL_MOUSEBUTTONUP: // Release Mouse
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				Mouse::SetLMB(false);
				break;
			case SDL_BUTTON_RIGHT:
				Mouse::SetRMB(false);
				break;

			default:
				break;
			}
			break;

		case SDL_KEYDOWN: // Button press
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				Keyboard::SetArrowUP(true);
				break;
			case SDLK_DOWN:
				Keyboard::SetArrowDown(true);
				break;
			case SDLK_LEFT:
				Keyboard::SetArrowLeft(true);
				break;
			case SDLK_RIGHT:
				Keyboard::SetArrowRight(true);
				break;

			case SDLK_w:
				Keyboard::SetKeyW(true);
				break;
			case SDLK_s:
				Keyboard::SetKeyS(true);
				break;
			case SDLK_a:
				Keyboard::SetKeyA(true);
				break;
			case SDLK_d:
				Keyboard::SetKeyD(true);
				break;

			case SDLK_r:
				Keyboard::SetKeyR(true);
				break;
			case SDLK_h:
				Keyboard::SetKeyH(true);
				break;

			case SDLK_0:
				Keyboard::SetKey_0(true);
				break;
			case SDLK_1:
				Keyboard::SetKey_1(true);
				break;
			case SDLK_2:
				Keyboard::SetKey_2(true);
				break;
			case SDLK_3:
				Keyboard::SetKey_3(true);
				break;
			case SDLK_4:
				Keyboard::SetKey_4(true);
				break;
			case SDLK_5:
				Keyboard::SetKey_5(true);
				break;
			case SDLK_6:
				Keyboard::SetKey_6(true);
				break;
			case SDLK_7:
				Keyboard::SetKey_7(true);
				break;
			case SDLK_8:
				Keyboard::SetKey_8(true);
				break;
			case SDLK_9:
				Keyboard::SetKey_9(true);
				break;
			}
			break;

		case SDL_KEYUP: // Button release
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				Keyboard::SetArrowUP(false);
				break;
			case SDLK_DOWN:
				Keyboard::SetArrowDown(false);
				break;
			case SDLK_LEFT:
				Keyboard::SetArrowLeft(false);
				break;
			case SDLK_RIGHT:
				Keyboard::SetArrowRight(false);
				break;

			case SDLK_w:
				Keyboard::SetKeyW(false);
				break;
			case SDLK_s:
				Keyboard::SetKeyS(false);
				break;
			case SDLK_a:
				Keyboard::SetKeyA(false);
				break;
			case SDLK_d:
				Keyboard::SetKeyD(false);
				break;

			case SDLK_r:
				Keyboard::SetKeyR(false);
				break;
			case SDLK_h:
				Keyboard::SetKeyH(false);
				break;

			case SDLK_0:
				Keyboard::SetKey_0(false);
				break;
			case SDLK_1:
				Keyboard::SetKey_1(false);
				break;
			case SDLK_2:
				Keyboard::SetKey_2(false);
				break;
			case SDLK_3:
				Keyboard::SetKey_3(false);
				break;
			case SDLK_4:
				Keyboard::SetKey_4(false);
				break;
			case SDLK_5:
				Keyboard::SetKey_5(false);
				break;
			case SDLK_6:
				Keyboard::SetKey_6(false);
				break;
			case SDLK_7:
				Keyboard::SetKey_7(false);
				break;
			case SDLK_8:
				Keyboard::SetKey_8(false);
				break;
			case SDLK_9:
				Keyboard::SetKey_9(false);
				break;
			}
			break;

		case SDL_QUIT:
			running = false;
			break;

		default:
			break;
		}
	}

	// Update mouse world position
	Vector2D<> camLoc = camera->getComponent<CameraManagerComponent>().getCameraPosition();
	Mouse::SetWorldMouse(Mouse::GetScreenMouseX() + camLoc.X, Mouse::GetScreenMouseY() + camLoc.Y);
}
