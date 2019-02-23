#pragma once

struct SDL_Renderer;

namespace Shapes 
{
	void drawCircle(SDL_Renderer * renderer, int x, int y, int radius);

	void DrawLimitedLine(SDL_Renderer * renderer, int x1, int y1, int x2, int y2, int lineLength);
}