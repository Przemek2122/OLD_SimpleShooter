#pragma once
#include "game.h"
#include "SDL.h"

namespace Shapes
{
	void drawCircle(SDL_Renderer * renderer, int x, int y, int radius)
	{
		int nx = radius - 1;
		int ny = 0;
		int dx = 1;
		int dy = 1;
		int err = dx - (radius << 1);

		while (nx >= ny)
		{
			SDL_RenderDrawPoint(renderer, x + nx, y + ny);
			SDL_RenderDrawPoint(renderer, x + ny, y + nx);
			SDL_RenderDrawPoint(renderer, x - ny, y + nx);
			SDL_RenderDrawPoint(renderer, x - nx, y + ny);
			SDL_RenderDrawPoint(renderer, x - nx, y - ny);
			SDL_RenderDrawPoint(renderer, x - ny, y - nx);
			SDL_RenderDrawPoint(renderer, x + ny, y - nx);
			SDL_RenderDrawPoint(renderer, x + nx, y - ny);

			if (err <= 0)
			{
				ny++;
				err += dy;
				dy += 2;
			}

			if (err > 0)
			{
				nx--;
				dx += 2;
				err += dx - (radius << 1);
			}
		}
	}

	void DrawLimitedLine(SDL_Renderer * renderer, int x1, int y1, int x2, int y2, int lineLength)
	{
		int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
		int dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
		int err = (dx > dy ? dx : -dy) / 2;

		int i = 0;
		while (SDL_RenderDrawPoint(renderer, x1, y1), i < lineLength)
		{
			int e2 = err;
			if (e2 > -dx) { err -= dy; x1 += sx; }
			if (e2 < dy) { err += dx; y1 += sy; }
			i++;
		}
	}
}