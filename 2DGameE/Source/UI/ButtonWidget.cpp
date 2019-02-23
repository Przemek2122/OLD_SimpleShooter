#include "ButtonWidget.h"
#include "../Mouse.h"


ButtonWidget::ButtonWidget(int x, int y, int width, int height)
{
	button.x = x,
	button.y = y,
	button.w = width,
	button.h = height;

	mButtonState = BUTTON_MOUSE_OUT;

	textureID = "ui_button_default";
	setTexture(textureID);
}

ButtonWidget::~ButtonWidget()
{
	SDL_free(texture);
}

void ButtonWidget::update()
{
	if (Mouse::GetScreenMouseX() == 0 && Mouse::GetScreenMouseY() == 0)
		return;

	// Check if mouse is in button 
	bool inside = true;
	if (Mouse::GetScreenMouseX() < button.x || Mouse::GetScreenMouseX() > button.x + button.w
	||  Mouse::GetScreenMouseY() < button.y || Mouse::GetScreenMouseY() > button.y + button.h)
	{
		inside = false;
	}

	// Mouse outside
	if (!inside)
	{
		if (mButtonState != BUTTON_MOUSE_OUT)
		{
			mButtonState = BUTTON_MOUSE_OUT;
			onMouseOut();
		}
	}
	// Mouse is inside button 
	else
	{
		if (Mouse::GetLMB())
		{
			if (mButtonState != BUTTON_MOUSE_DOWN)
			{
				if (mButtonState != BUTTON_MOUSE_DOWN && mButtonState != BUTTON_MOUSE_UP)
					onMouseOver(); // Mouse over button

				mButtonState = BUTTON_MOUSE_DOWN;
				onMouseDown(); // Button click
			}
		}
		else 
		{
			if (mButtonState != BUTTON_MOUSE_UP)
			{
				if (mButtonState != BUTTON_MOUSE_DOWN && mButtonState != BUTTON_MOUSE_UP)
					onMouseOver(); // Mouse over button

				mButtonState = BUTTON_MOUSE_UP;
				onMouseUP();   // Button release
			}
		}
	}
}

void ButtonWidget::render()
{
	SDL_Rect destRect;

	destRect.x = button.x;
	destRect.y = button.y;
	destRect.w = button.w;
	destRect.h = button.h;

	//if (texture == nullptr)
	//	Util::Error("texture is nullptr in render() in UIButton");
	//if (Game::renderer == nullptr)
	//	Util::Error("renderer is nullptr in render() in UIButton");

	SDL_RenderCopyEx(Game::renderer, texture, nullptr, &destRect, angle, &center, renderFlip);
}

void ButtonWidget::setTexture(const char * texID)
{
	textureID = texID;
	texture = Game::assets->getRawTexture(textureID);
}

void ButtonWidget::onMouseOut()
{
	Util::Debug("BUTTON_MOUSE_OUT");
}

void ButtonWidget::onMouseOver()
{
	Util::Debug("BUTTON_MOUSE_OVER");
}

void ButtonWidget::onMouseDown()
{
	Util::Debug("BUTTON_MOUSE_DOWN");
}

void ButtonWidget::onMouseUP()
{
	Util::Debug("BUTTON_MOUSE_UP");
}