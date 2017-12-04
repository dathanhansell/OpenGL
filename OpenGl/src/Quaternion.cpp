#include "Quaternion.h"
#include <string>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>
const float DEG2RAD = M_PI / 180.0f;
const float RAD2DEG = 180.0f / M_PI;
const float EPSILON = 0.00001f;
Quaternion::Quaternion() {
	x = 0; y = 0; z = 0; w = 0;
}
Quaternion::Quaternion(float X, float Y, float Z, float W) {
	x = X; y = Y; z = Z; w = W;
}
Quaternion& Quaternion::Rotate(Vector3 angle) {
	return Rotate(angle.x, angle.y, angle.z);
}
Quaternion& Quaternion::Rotate(float X, float Y, float Z) {
	X *= DEG2RAD;
	Y *= DEG2RAD;
	Z *= DEG2RAD;

	float c2 = cos(Z * 0.5)
		, s2 = sin(Z * 0.5)
		, c1 = cos(Y * 0.5)
		, s1 = sin(Y * 0.5)
		, c0 = cos(X * 0.5)
		, s0 = sin(X * 0.5);

	x = c1 * c2 * s0 + s1 * s2 * c0;
	y = s1 * c2 * c0 - c1 * s2 * s0;
	z = c1 * s2 * c0 - s1 * c2 * s0;
	w = c1 * c2 * c0 + s1 * s2 * s0;

	return *this;
}
Vector3 Quaternion::ToEuler() {
	float v = (y*z) + (x*w);
	if (abs(v - 0.5) < 1e-12) {
		return Vector3(2 * atan2(y, x), M_PI / 2, 0);
	}
	if (abs(v + 0.5) < 1e-12) {
		return Vector3(-2 * atan2(y, x), -M_PI / 2, 0);
	}
	return Vector3(atan2(2 * (x*z - y*w), 1 - 2 * (z*z + w*w)),
		asin(2 * v),
		atan2(2 * (x*y - z*w), 1 - 2 * (y*y + w*w)));
}
std::string Quaternion::ToString() {
	std::stringstream ss;
	ss << "{ x:" << x << " y:" << y << " z:" << z << " w:" << w << " }";
	return ss.str();
}
void Quaternion::Print(std::string title) {
	std::cout << title << this->ToString() << std::endl;
}
