#include "Quaternion.h"
#include <string>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>
#include <algorithm>
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

	float cz = cos(Z * .5)
		, sz = sin(Z * .5)
		, cy = cos(Y * .5)
		, sy = sin(Y * .5)
		, cx = cos(X * .5)
		, sx = sin(X * .5);

	x = cy * cz * sx + sy * sz * cx;
	y = sy * cz * cx - cy * sz * sx;
	z = cy * sz * cx - sy * cz * sx;
	w = cy * cz * cx + sy * sz * sx;
	/*
	x = cos(Y/2) * cos(Z/2) * sin(X/2) + sin(Y/2) * sin(Z/2) * cos(X/2);
	y = sin(Y/2) * cos(Z/2) * cos(X/2) - cos(Y/2) * sin(Z/2) * sin(X/2);
	z = cos(Y/2) * sin(Z/2) * cos(X/2) - sin(Y/2) * cos(Z/2) * sin(X/2);
	w = cos(Y/2) * cos(Z/2) * cos(X/2) + sin(Y/2) * sin(Z/2) * sin(X/2);

	x = cos(60 * (M_PI / 180) * .5) * cos(90 * (M_PI / 180) * .5) * sin(30 * (M_PI / 180) * .5) + sin(60 * (M_PI / 180) * .5) * sin(90 * (M_PI / 180) * .5) * cos(30 * (M_PI / 180) * .5);
	y = sin(60 * (M_PI / 180) * .5) * cos(90 * (M_PI / 180) * .5) * cos(30 * (M_PI / 180) * .5) - cos(60 * (M_PI / 180) * .5) * sin(90 * (M_PI / 180) * .5) * sin(30 * (M_PI / 180) * .5);
	z = cos(60 * (M_PI / 180) * .5) * sin(90 * (M_PI / 180) * .5) * cos(30 * (M_PI / 180) * .5) - sin(60 * (M_PI / 180) * .5) * cos(90 * (M_PI / 180) * .5) * sin(30 * (M_PI / 180) * .5);
	w = cos(60 * (M_PI / 180) * .5) * cos(90 * (M_PI / 180) * .5) * cos(30 * (M_PI / 180) * .5) + sin(60 * (M_PI / 180) * .5) * sin(90 * (M_PI / 180) * .5) * sin(30 * (M_PI / 180) * .5);
	*/
	return *this;
}
void Quaternion::Normalize(){
	float magnitude = sqrt(pow(w, 2) + pow(x, 2) + pow(y, 2) + pow(z, 2));
	w = w / magnitude;
	x = x / magnitude;
	y = y / magnitude;
	z = z / magnitude;
	}

Vector3 Quaternion::ToEuler() {
	Vector3 e;
	float sx = 2 * (w * x + y * z);
	float cx = 1 - 2 * (x * x + y * y);
	e.x = atan2(sx, cx);

	float sy = 2 * (w * y - z * x);
	if (fabs(sx) >= 1)
		e.y = copysign(M_PI / 2, sx);
	else
		e.y = asin(sx);

	float sz = 2 * (w * z + x * y);
	float cz = 1 - 2 * (y * y + z * z);
	e.z = atan2(sy, cz); 
	e *= RAD2DEG;
		e.print("\nTOEULERCALL: ");
	return e;
}
std::string Quaternion::ToString() {
	std::stringstream ss;
	ss << "{ x:" << x << " y:" << y << " z:" << z << " w:" << w << " }";
	return ss.str();
}
void Quaternion::Print(std::string title) {
	std::cout << title << this->ToString() << std::endl;
}
