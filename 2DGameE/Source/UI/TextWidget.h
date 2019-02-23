#pragma once
#include "UI.h"


class TextWidget : public Widget {
public:
	TextWidget(int x, int y, std::string text, std::string font, SDL_Color& color);
	~TextWidget();

	void enable();

	void disable();

	void set(int x, int y, std::string text, std::string font, SDL_Color& color);

	void setText(std::string text, std::string font);

	void render() override;

private:
	SDL_Rect textbox;
	SDL_Color textColor;
	SDL_Texture * texture = nullptr;

};