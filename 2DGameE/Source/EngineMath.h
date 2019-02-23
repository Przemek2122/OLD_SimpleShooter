#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector2D.h"
#include <vector>
#include "SDL.h"


namespace EMath
{
	#define ROUND_INT(f) ((int)(f >= 0.0 ? (f + 0.5) : (f - 0.5)))

	float RandomFloat(float a, float b);

	float RadiansToDegrees(float x);
	
	double RadiansToDegreesDouble(double x);

	float DegreesToRadians(float x);

	double DegreesToRadiansDouble(double x);

	/* Returns radians */
	double Get2DAngleOfPointRadians(Vector2D<> a, Vector2D<> b);

	/* Expects radians not degree */
	void RotatePointArroundPoint(Vector2D<int> & pivot, float & angle, Vector2D<int>& point);

	Vector2D<int>* RotateRect(SDL_Rect rect, Vector2D<int> center, float angle);

	void RotatePoints(std::vector<Vector2D<int>> & points, Vector2D<int> & center, float & angle);

	int RoundAngleInt(int x);

	float RoundAngleFloat(int x);

	float Distance2D(Vector2D<> a, Vector2D<> b);

	Vector2D<int> GetRectCenter(SDL_Rect rect);

};
