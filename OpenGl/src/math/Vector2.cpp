#include "Vector2.h"
#include "cmath"      // for sqrt
#include "exception"  // for uncaught_exception
#include "iosfwd"     // for ostringstream, ostream
#include "iostream"   // for cout
#include "ostream"    // for operator<<, basic_ostream, basic_ostream<>::_Myt, endl
#include "sstream"    // for basic_ostringstream
#include <string>     // for char_traits

	Vector2::Vector2()
	{
		x = 0;
		y = 0;
	}
	Vector2::Vector2(float X, float Y)
	{
		x = X;
		y = Y;
	}
	Vector2& Vector2::operator+(const Vector2& a)
	{
		return Vector2(a.x + x, a.y + y);
	}
	Vector2& Vector2::operator-(const Vector2& a)
	{
		return Vector2(x - a.x, y - a.y);
	}
	Vector2& Vector2::operator*(const Vector2& a)
	{
		return Vector2(a.x * x, a.y * y);
	}
	Vector2& Vector2::operator+=(const Vector2& a)
	{
		x += a.x;
		y += a.y;
		return *this;
	}
	Vector2& Vector2::operator*=(const Vector2& a)
	{
		x *= a.x;
		y *= a.y;
		return *this;
	}
	bool Vector2::operator!=(const Vector2& a)
	{
		return x != a.x || y != a.y;
	}
	Vector2& Vector2::operator-() const {
		return Vector2(-x, -y);
	}
	Vector2& Vector2::operator*(const float& a)
	{
		return Vector2(x * a, y * a);
	}
	Vector2& Vector2::operator/(const float& a)
	{
		return Vector2(x / a, y / a);
	}
	Vector2& Vector2::operator*=(const float& a)
	{
		x *= a;
		y *= a;
		return *this;
	}
	void Vector2::Normalize()
	{
		float m = sqrt(x * x + y * y);
		x /= m;
		y /= m;
	}
	float Vector2::Dot(Vector2 v1, Vector2 v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	Vector2 Vector2::normalized()
	{
		float m = sqrt(x * x + y * y);
		return Vector2(x / m, y / m);
	}
	float Vector2::magnitude()
	{
		return sqrt(x * x + y * y);
	}
	void Vector2::print()
	{
		std::cout << "X: " << x << " Y: " << y << std::endl;
	}
	void Vector2::print(char* title)
	{
		std::cout << title << "X: " << x << " Y: " << y << std::endl;
	}
	tString Vector2::ToString()
	{
		std::ostringstream buffer;
		buffer << "X: " << x << " Y: " << y;
		return buffer.str();
	}
