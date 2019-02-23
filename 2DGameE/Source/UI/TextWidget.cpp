#include "TextWidget.h"


TextWidget::TextWidget(int x, int y, std::string text, std::string font, SDL_Color& color) 
{
	textbox = { x, y, 0, 0 };
	textColor = color;

	// Set text
	SDL_Surface * textSurface = TTF_RenderText_Blended(Game::assets->getFont(font), text.c_str(), textColor);
	texture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	SDL_FreeSurface(textSurface);
}

TextWidget::~TextWidget()
{
	// Free memory
	SDL_free(texture);
}

void TextWidget::enable()
{
	renderEnabled = true;
	updateEnabled = true;
}

void TextWidget::disable()
{
	renderEnabled = false;
	updateEnabled = false;
}

void TextWidget::set(int x, int y, std::string text, std::string font, SDL_Color & color)
{
	textbox = { x, y, 0, 0 };
	textColor = color;

	// Set text
	SDL_Surface * textSurface = TTF_RenderText_Blended(Game::assets->getFont(font), text.c_str(), textColor);
	texture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	SDL_FreeSurface(textSurface);
}

// Use after adding UIText and init(), this function changes text and font
void TextWidget::setText(std::string text, std::string font) 
{
	// Make sure this text exists
	// TBF

	SDL_Surface * textSurface = TTF_RenderText_Blended(Game::assets->getFont(font), text.c_str(), textColor);
	SDL_LockSurface(textSurface); // Lock surface for safe pixel acces

	if (textbox.w != textSurface->w || textbox.h != textSurface->h) {
		// Destroy old texture
		SDL_free(texture);

		// Create new texture
		texture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	}
	else {
		// if size not changed update old texture
		SDL_UpdateTexture(texture, NULL, textSurface->pixels, textSurface->pitch);
	}

	SDL_FreeSurface(textSurface);
	SDL_QueryTexture(texture, NULL, NULL, &textbox.w, &textbox.h);
}

void TextWidget::render()
{
	SDL_RenderCopy(Game::renderer, texture, nullptr, &textbox);
}