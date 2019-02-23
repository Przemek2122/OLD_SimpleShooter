#include "DynamicCollision.h"
#include "SDL.h"
#include "Circle.h"
#include "EngineMath.h"



bool Collision::rectangleCollision(SDL_Rect rect1, SDL_Rect rect2)
{
	if ((rect1.x + rect1.w) >= (rect2.x - 1)		// object 1 hitting left side of object 2
	&& (rect1.x - 1) <= (rect2.x + rect2.w)			// object 1 hitting right side of object 2
	&& (rect1.y - 1) <= (rect2.y + rect2.h)			// Object 1 hitting bottom of object 2 (assuming your y goes from top to bottom of screen)
	&& (rect1.y + rect1.h) >= (rect2.y - 1))		// Object 1 hitting top of object 2
	{
		return true;	
	}

	return false; // The rects do not overlap:
}

bool Collision::rectangleCollision(SDL_Rect rect1, SDL_Rect rect2, float angle)
{
	// TL - Top Left, TR - Top Right
	// BL - Bottom Left, BR - Bottom Right

	/*Vector2D<> Axis1.X = A.UR.X - A.UL.X;
	Axis1.Y = A.UR.Y - A.UL.Y;
	Vector2D<>Axis2.X = A.UR.X - A.LR.X;
	Axis2.Y = A.UR.Y - A.LR.Y;
	Vector2D<>Axis3.X = B.UL.X - B.LL.X;
	Axis3.Y = B.UL.Y - B.LL.Y;
	Vector2D<>Axis4.X = B.UL.X - B.UR.X;
	Axis4.Y = B.UL.Y - B.UR.Y;*/

	return false;
}

int Collision::rectangleCollisionPrecise(SDL_Rect rect1, SDL_Rect rect2)
{
	if		((rect1.x + rect1.w) >= (rect2.x - 1)) return 1;	// object 1 hitting left side of object 2
	else if ((rect1.x - 1) <= (rect2.x + rect2.w)) return 2;	// object 1 hitting right side of object 2
	else if ((rect1.y - 1) <= (rect2.y + rect2.h)) return 3;	// Object 1 hitting bottom of object 2 (assuming your y goes from top to bottom of screen)
	else if ((rect1.y + rect1.h) >= (rect2.y - 1)) return 4;	// Object 1 hitting top of object 2

	return 0; // The rects do not overlap:
}

int Collision::circleCollision(Circle circle1, Circle circle2)
{
	if (circle1.x + circle1.radius + circle2.radius > circle2.x
	&& circle1.x < circle2.x + circle1.radius + circle2.radius
	&& circle1.y + circle1.radius + circle2.radius > circle2.y
	&& circle1.y < circle2.y + circle1.radius + circle2.radius)
	{
		// Rectangle Overlap of 

		double distance = sqrt(
			((circle1.x - circle2.x) * (circle1.x - circle2.x))
			+ ((circle1.y - circle2.y) * (circle1.y - circle2.y))
		);
		if (ROUND_INT(distance) < circle1.radius + circle2.radius)
		{
			// Circles have collided

			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}


