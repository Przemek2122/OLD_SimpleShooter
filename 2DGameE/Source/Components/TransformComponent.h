#pragma once
#include "../Vector2D.h"
#include "sdl.h"

class TransformComponent : public Component {
public:
	TransformComponent(int h = 32, int w = 32, int x = 0, int y = 0, Vector2D<> location = Vector2D<>(0, 0))
		: Rect({ x, y, h, w }), Location(location) {}
	~TransformComponent() {}

	Vector2D<> Location; // stores x and y pos
	int Rotation = 0; // Angle
	SDL_Rect Rect;

	void setTransform(int x, int y);

	Vector2D<> getWorldLocation();
	Vector2D<> getLocation();

};