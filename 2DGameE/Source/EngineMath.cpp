#include "EngineMath.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <complex> 


float EMath::RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

float EMath::RadiansToDegrees(float x)
{
	return (float)RoundAngleFloat(x * 180 / M_PI);
}

double EMath::RadiansToDegreesDouble(double x)
{
	return x * 180 / M_PI;
}

float EMath::DegreesToRadians(float x)
{
	return (float)(2 * M_PI * (x / 360));
}

double EMath::DegreesToRadiansDouble(double x)
{
	return (double)(2 * M_PI * (x / 360));
}

double EMath::Get2DAngleOfPointRadians(Vector2D<> a, Vector2D<> b)
{
	return atan2(a.Y - b.Y, a.X - b.X);
}

Vector2D<int> * EMath::RotateRect(SDL_Rect rect, Vector2D<int> center, float angle)
{
	std::vector<Vector2D<int>> points;

	// Get corners
	// Left top
	points.emplace_back(rect.x, rect.y);
	// Right top
	points.emplace_back(rect.x + rect.w, rect.y);
	// Left bottom
	points.emplace_back(rect.x, rect.y + rect.h);
	// Right bottom
	points.emplace_back(rect.x + rect.w, rect.y + rect.h);

	RotatePoints(points, center, angle);

	Vector2D<int> vertices[4];
	vertices[0] = points[0];
	vertices[1] = points[1];
	vertices[2] = points[2];
	vertices[3] = points[3];

	return vertices;
}

void inline EMath::RotatePoints(std::vector<Vector2D<int>> & points, Vector2D<int> & center, float & angle)
{
	for (int i = 0; i < points.size(); i++)
	{
		RotatePointArroundPoint(center, angle, points[i]);
	}
}

void inline EMath::RotatePointArroundPoint(Vector2D<int> &pivot, float &angle, Vector2D<int> &point)
{
	float s = sin(angle);
	float c = cos(angle);

	// translate point back to origin:
	point.X -= pivot.X;
	point.Y -= pivot.Y;

	// rotate point
	float xnew = point.X * c - point.Y * s;
	float ynew = point.X * s + point.Y * c;

	// translate point back:
	point.X = xnew + pivot.X;
	point.Y = ynew + pivot.Y;
}

/** Rounds x to be between 0 and 360 eg: 720 will be 360, 480 will be 120 etc.  */
int inline EMath::RoundAngleInt(int x)
{
	while (x > 360)
		x -= 360;

	while (x < 0)
		x += 360;

	return (int)x;
}

/** Rounds x to be between 0 and 360 eg: 720 will be 360, 480 will be 120 etc.  */
float inline EMath::RoundAngleFloat(int x)
{
	while (x > 360)
		x -= 360;

	while (x < 0)
		x += 360;

	return (float)x;
}

float EMath::Distance2D(Vector2D<> a, Vector2D<> b)
{
	// Just a^2 + b^2 = c^2

	int distancex = (b.X - a.X) * (b.X - a.X);
	int distancey = (b.Y - a.Y) * (b.Y - a.Y);

	// Then just square root

	return (float)sqrt(distancex + distancey);
}

Vector2D<int> EMath::GetRectCenter(SDL_Rect rect)
{
	return Vector2D<int>(rect.x + (rect.w / 2), rect.y + (rect.h / 2));
}
