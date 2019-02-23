#pragma once
#include "UI.h"


enum ButtonState
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_MOUSE_DOWN = 2,
	BUTTON_MOUSE_UP = 3,
};

class ButtonWidget : public  Widget {
public:
	ButtonWidget(int butt_x, int butt_y, int butt_width, int butt_height);
	~ButtonWidget();

	void update() override;
	void render() override;

	void setTexture(const char * texID);

	void onMouseOver();
	void onMouseOut();
	void onMouseDown();
	void onMouseUP();

private:
	SDL_Rect button;
	SDL_Point center;
	float angle;
	const char * textureID;
	const char * texturePath;
	SDL_Texture * texture = nullptr;
	ButtonState mButtonState;
	SDL_RendererFlip renderFlip;

};