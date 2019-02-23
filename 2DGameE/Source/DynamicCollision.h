#pragma once
#include "Components/ECS.h"


struct SDL_Rect;
struct Circle;

class Collision
{
public:
	/* Returns false if there is no collision.
	 * Returns true if there is collision on left side. */
	static bool rectangleCollision(SDL_Rect rect1, SDL_Rect rect2);

	/* Rectangle collision with rotation support. Standard Bounds-based:
	 * https://www.gamedev.net/articles/programming/general-and-gameplay-programming/2d-rotated-rectangle-collision-r2604 */
	static bool rectangleCollision(SDL_Rect rect1, SDL_Rect rect2, float angle);

	/* Returns 0 if there is no collision.
	 * Returns 1 if there is collision on left side.
	 * Returns 2 if there is collision on right side.
	 * Returns 3 if there is collision on bottom side.
	 * Returns 4 if there is collision on top side. */
	static int rectangleCollisionPrecise(SDL_Rect rect1, SDL_Rect rect2);

	/* Returns 0 if there is no collision
	 * Returns 1 if there is collision. */
	static int circleCollision(Circle circle1, Circle circle2);

};