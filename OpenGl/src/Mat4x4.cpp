#include "Mat4x4.h"
#include <string>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>
const float DEG2RAD = 3.141593f / 180.0f;
const float RAD2DEG = 180.0f / 3.141593f;
const float EPSILON = 0.00001f;
Mat4x4::Mat4x4() {
	m[0] = 0; m[4] = 0; m[8] = 0; m[12] = 0;
	m[1] = 0; m[5] = 0;	m[9] = 0; m[13] = 0;
	m[2] = 0; m[6] = 0;	m[10] = 0; m[14] = 0;
	m[3] = 0; m[7] = 0;	m[11] = 0; m[15] = 0;
}
Mat4x4::Mat4x4(const float src[16]) {
	m[0] = src[0]; m[4] = src[4];   m[8] = src[8];  m[12] = src[12];
	m[1] = src[1]; m[5] = src[5];	m[9] = src[9];  m[13] = src[13];
	m[2] = src[2]; m[6] = src[6];	m[10] = src[10]; m[14] = src[14];
	m[3] = src[3]; m[7] = src[7];	m[11] = src[11]; m[15] = src[15];
}
Mat4x4::Mat4x4(float m00, float m01, float m02, float m03,
	float m04, float m05, float m06, float m07,
	float m08, float m09, float m10, float m11,
	float m12, float m13, float m14, float m15) {
	m[0] = m00; m[4] = m04;   m[8] = m08;  m[12] = m12;
	m[1] = m01; m[5] = m05;	m[9] = m09;  m[13] = m13;
	m[2] = m02; m[6] = m06;	m[10] = m10; m[14] = m14;
	m[3] = m03; m[7] = m07;	m[11] = m11; m[15] = m15;
}
Mat4x4& Mat4x4::Translate(const Vector3& v)
{
	return Translate(v.x, v.y, v.z);
}
Mat4x4& Mat4x4::Translate(float x, float y, float z)
{
	m[0] += m[3] * x;   m[4] += m[7] * x;   m[8] += m[11] * x;   m[12] += m[15] * x;
	m[1] += m[3] * y;   m[5] += m[7] * y;   m[9] += m[11] * y;   m[13] += m[15] * y;
	m[2] += m[3] * z;   m[6] += m[7] * z;   m[10] += m[11] * z;   m[14] += m[15] * z;

	return *this;
}
Mat4x4& Mat4x4::Scale(float s)
{
	return Scale(s, s, s);
}
Mat4x4& Mat4x4::Scale(float x, float y, float z)
{
	m[0] *= x;   m[4] *= x;   m[8] *= x;   m[12] *= x;
	m[1] *= y;   m[5] *= y;   m[9] *= y;   m[13] *= y;
	m[2] *= z;   m[6] *= z;   m[10] *= z;   m[14] *= z;
	return *this;
}
Mat4x4& Mat4x4::Perspective(float fov, float aspectRatio, float zNear, float zFar)
{
	float tanHalfFOV = (float)tan(fov / 2);
	float zRange = zNear - zFar;

	m[0] = 1.0f / (tanHalfFOV * aspectRatio);	m[4] = 0;		m[8] = 0;	m[12] = 0;
	m[1] = 0;						m[5] = 1.0f / tanHalfFOV;	m[9] = 0;	m[13] = 0;
	m[2] = 0;						m[6] = 0;					m[10] = (-zNear - zFar) / zRange;	m[15] = 2 * zFar * zNear / zRange;
	m[3] = 0;						m[7] = 0;					m[11] = 1;	m[14] = 0;

	return *this;
}
Mat4x4& Mat4x4::Orthographic(float left, float right, float bottom, float top, float near, float far)
{
	float width = right - left;
	float height = top - bottom;
	float depth = far - near;

	m[0] = 2 / width; m[4] = 0;			 m[8] = 0;			 m[12] = -(right + left) / width;
	m[1] = 0;		  m[5] = 2 / height; m[9] = 0;			 m[13] = -(top + bottom) / height;
	m[2] = 0;		  m[6] = 0;		 	 m[10] = -2 / depth; m[14] = -(far + near) / depth;
	m[3] = 0;		  m[7] = 0;			 m[11] = 0;			 m[15] = 1;

	return *this;
}
Mat4x4& Mat4x4::View(Vector3 eye, Vector3 target, Vector3 up)
{
	Vector3 zaxis = (eye - target).normalized();
	Vector3 xaxis = Vector3::Cross(up, zaxis).normalized();
	Vector3 yaxis = Vector3::Cross(zaxis, xaxis).normalized();

	m[0] = xaxis.x;					  m[4] = yaxis.x;					m[8] = zaxis.x;					   m[12] = 0;
	m[1] = xaxis.y;					  m[5] = yaxis.y;					m[9] = zaxis.y, m[13] = 0;
	m[2] = xaxis.z;					  m[6] = yaxis.z;					m[10] = zaxis.z, m[14] = 0;
	m[3] = -Vector3::Dot(xaxis, eye); m[7] = -Vector3::Dot(yaxis, eye); m[11] = -Vector3::Dot(zaxis, eye); m[15] = 1;

	return *this;
}
/*
Mat4x4& Mat4x4::rotate(Vector3 angle)
{
return rotate(angle.x, angle.y, angle.z);
}

Mat4x4& Mat4x4::rotate(float x, float y, float z)
{
float c = 0;
float s = 0;
//float c = cosf(angle * DEG2RAD);
//float s = sinf(angle * DEG2RAD);
float c1 = 1.0f - c;
float m0 = m[0], m4 = m[4], m8 = m[8], m12 = m[12],
m1 = m[1], m5 = m[5], m9 = m[9], m13 = m[13],
m2 = m[2], m6 = m[6], m10 = m[10], m14 = m[14];

// build rotation matrix
float r0 = x * x * c1 + c;
float r1 = x * y * c1 + z * s;
float r2 = x * z * c1 - y * s;
float r4 = x * y * c1 - z * s;
float r5 = y * y * c1 + c;
float r6 = y * z * c1 + x * s;
float r8 = x * z * c1 + y * s;
float r9 = y * z * c1 - x * s;
float r10 = z * z * c1 + c;

// multiply rotation matrix
m[0] = r0 * m0 + r4 * m1 + r8 * m2;
m[1] = r1 * m0 + r5 * m1 + r9 * m2;
m[2] = r2 * m0 + r6 * m1 + r10* m2;
m[4] = r0 * m4 + r4 * m5 + r8 * m6;
m[5] = r1 * m4 + r5 * m5 + r9 * m6;
m[6] = r2 * m4 + r6 * m5 + r10* m6;
m[8] = r0 * m8 + r4 * m9 + r8 * m10;
m[9] = r1 * m8 + r5 * m9 + r9 * m10;
m[10] = r2 * m8 + r6 * m9 + r10* m10;
m[12] = r0 * m12 + r4 * m13 + r8 * m14;
m[13] = r1 * m12 + r5 * m13 + r9 * m14;
m[14] = r2 * m12 + r6 * m13 + r10* m14;

return *this;
}
*/
Vector3& Mat4x4::Rotate(Vector3 angle)
{
	Vector3 f = Vector3::forward;
	Vector3 r = Vector3::right;
	Vector3 u = Vector3::up;

	f = Vector3::EulerToForwardVector(angle);
	r = Vector3::Cross(u, f).normalized();
	u = Vector3::Cross(f, r);

	//m[0] = cos(x) * -sin(y)
	return Vector3(0, 0, 0);
}