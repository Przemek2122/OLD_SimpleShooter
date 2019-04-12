#pragma once
#include <iostream>
#include <string>
#include <cfloat>
#include <climits>

/* T is type of x and y (Can be float can be double, etc). */
template<class T = float>
class Vector2D
{
public:
	T X;
	T Y;

	Vector2D() : X(T(0)), Y(T(0)) {}
	Vector2D(const T x, const T y) : X(x), Y(y) {}
	template<typename oldType>
	Vector2D(Vector2D<oldType> oldVector) { X = (T)oldVector.X; Y = (T)oldVector.Y; }

	// Comparsion
	template<typename oldType>
	Vector2D operator=(const Vector2D<oldType> &oldVector) { X = (T)oldVector.X; Y = (T)oldVector.Y; return *this; }

	// Set to negative value
	Vector2D operator-() const { return Vector2D(-X, -Y); }

	// Basic calculations
	friend Vector2D operator+(const Vector2D<T>& v1, const Vector2D<T>& v2) { return Vector2D<T>(v1.X + v2.X, v1.Y + v2.Y); }
	friend Vector2D operator-(const Vector2D<T>& v1, const Vector2D<T>& v2) { return Vector2D<T>(v1.X - v2.X, v1.Y - v2.Y); }
	friend Vector2D operator*(const Vector2D<T>& v1, const Vector2D<T>& v2) { return Vector2D<T>(v1.X * v2.X, v1.Y * v2.Y); }
	friend Vector2D operator/(const Vector2D<T>& v1, const Vector2D<T>& v2) { return Vector2D<T>(v1.X / v2.X, v1.Y / v2.Y); }

	template <typename othertype>
	friend Vector2D operator+(const Vector2D<othertype>& v1, const Vector2D<T>& v2) { return Vector2D<T>((T)v1.X + v2.X, (T)v1.Y + v2.Y); }
	template <typename othertype>
	friend Vector2D operator-(const Vector2D<othertype>& v1, const Vector2D<T>& v2) { return Vector2D<T>(v1.X - v2.X, v1.Y - v2.Y); }
	template <typename othertype>
	friend Vector2D operator*(const Vector2D<othertype>& v1, const Vector2D<T>& v2) { return Vector2D<T>(v1.X * v2.X, v1.Y * v2.Y); }
	template <typename othertype>
	friend Vector2D operator/(const Vector2D<othertype>& v1, const Vector2D<T>& v2) { return Vector2D<T>(v1.X / v2.X, v1.Y / v2.Y); }

	Vector2D& operator+=(const Vector2D& v) { X += v.X; Y += v.Y; return *this; }
	Vector2D& operator-=(const Vector2D& v) { X -= v.X; Y -= v.Y; return *this; }
	Vector2D& operator*=(const Vector2D& v) { X *= v.X; Y *= v.Y; return *this; }
	Vector2D& operator/=(const Vector2D& v) { X /= v.X; Y /= v.Y; return *this; }

	// Comparsion
	friend bool operator==(const Vector2D& L, const Vector2D& R) { return std::tie(L.X, L.Y) == std::tie(R.X, R.Y); }
	friend bool operator!=(const Vector2D& L, const Vector2D& R) { return !(L == R); }
	friend bool operator< (const Vector2D& L, const Vector2D& R) { return std::tie(L.X, L.Y) < std::tie(R.X, R.Y); }
	friend bool operator>=(const Vector2D& L, const Vector2D& R) { return !(L < R); }
	friend bool operator> (const Vector2D& L, const Vector2D& R) { return   R < L; }
	friend bool operator<=(const Vector2D& L, const Vector2D& R) { return !(R < L); }


	// Coments below aren't tested...

	//Vector2D& operator*=(const& T v) { x *= v; y *= v; return *this; }
	//Vector2D& operator/=(const& T v) { x /= v; y /= v; return *this; }

	//template<class T> Vector2D<T> operator*(const T& s, const Vector2D<T>& v) { return Vector2D<T>(v) *= s; }
	//template<class T> Vector2D<T> operator*(const Vector2D<T>& v, const T& s) { return Vector2D<T>(v) *= s; }
	//template<class T> Vector2D<T> operator/(const T& s, const Vector2D<T>& v) { return Vector2D<T>(v) /= s; }
	//template<class T> Vector2D<T> operator/(const Vector2D<T>& v, const T& s) { return Vector2D<T>(v) /= s; }

	//template<class T> T DotProduct(const Vector2d<T>&, const Vector2d<T>&);
	//template<class T> T CrossProduct(const Vector2d<T>&, const Vector2d<T>&);

	////Returns the length of the vector from the origin.
	//template<class T> T EuclideanNorm(const Vector2d<T>&);

	//// Return the unit vector of the input
	//template<class T> Vector2d<T> Normal(const Vector2d<T>&);

	////Return a vector perpendicular to the left.
	//template<class T> Vector2d<T> Perpendicular(const Vector2d<T>&);

	////Return true if two line segments intersect.
	//template<class T> bool Intersect(const Vector2d<T>&, const Vector2d<T>&, const Vector2d<T>&, const Vector2d<T>&);

	////Return the point where two lines intersect.
	//template<class T> Vector2d<T> GetIntersect(const Vector2d<T>&, const Vector2d<T>&, const Vector2d<T>&, const Vector2d<T>&)

	Vector2D& Zero() { X = T(0); Y = T(0); }

	// Conversion
	operator std::ostream () const { std::ostream stream = "(" + X + "," + Y + ")"; return stream; }
	operator std::string () const { return "(" + std::to_string(X) + ", " + std::to_string(Y) + ")"; }

};
