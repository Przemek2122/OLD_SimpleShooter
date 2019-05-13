#include "UI.h"
#include <math.h>
#include "../Mouse.h"



namespace UIUtil {
	int getWindowWidth() {
		int w;
		SDL_GetWindowSize(Game::window, &w, NULL);
		return w;
	}

	int getWindowHeight() {
		int h;
		SDL_GetWindowSize(Game::window, NULL, &h);
		return h;
	}

	int getScreenPercentW(int p) {
		return (int)round(getWindowWidth() / 100 * p);
	}

	int getScreenPercentH(int p) {
		return (int)round(getWindowHeight() / 100 * p);
	}
};


UIManager::UIManager(Game * mGame)
{
	game = mGame;
}

UIManager::~UIManager(){}

void UIManager::update()
{
	for (auto& widget : Widgets)
		if (widget.second->isUpdateEnabled())
			widget.second->update();
}

void UIManager::render() 
{
	for (auto& widget : Widgets)
		if (widget.second->isRenderEnabled())
			widget.second->render();
}

bool UIManager::isThereWidgetWithID(std::string id)
{
	if (Widgets.find("f") == Widgets.end()) {
		// Not found
		return false;
	}
	else {
		// Found
		return true;
	}
}
