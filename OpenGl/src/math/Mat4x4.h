#pragma once
#include "Vector3.h"
#include "tString.h"

	class Mat4x4 {
	public:
		float m[16];
		Mat4x4();
		Mat4x4(const float src[16]);
		Mat4x4(float m00, float m01, float m02, float m03,
			float m04, float m05, float m06, float m07,
			float m08, float m09, float m10, float m11,
			float m12, float m13, float m14, float m15);
		Mat4x4& Identity();
		Mat4x4& Translate(const Vector3& v);
		Mat4x4& Translate(float x, float y, float z);
		Mat4x4& Scale(float s);
		Mat4x4& Scale(float x, float y, float z);
		Mat4x4& Scale(const Vector3& v);
		Mat4x4& Perspective(float fov, float aspectRatio, float zNear, float zFar);
		Mat4x4& Orthographic(float left, float right, float bottom, float top, float near, float far);
		Mat4x4& View(Vector3 eye, Vector3 target, Vector3 up);
		Mat4x4& setFrustum(float fovY, float aspect, float front, float back);
		Mat4x4& rotate(float angle, Vector3 axis);
		Mat4x4& rotate(float angle, float x, float y, float z);
		//Vector3& Rotate(Vector3 angle);
		tString toString();

		inline Mat4x4 Mat4x4::operator+(const Mat4x4& rhs) const
		{
			return Mat4x4(m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2], m[3] + rhs[3],
				m[4] + rhs[4], m[5] + rhs[5], m[6] + rhs[6], m[7] + rhs[7],
				m[8] + rhs[8], m[9] + rhs[9], m[10] + rhs[10], m[11] + rhs[11],
				m[12] + rhs[12], m[13] + rhs[13], m[14] + rhs[14], m[15] + rhs[15]);
		}

		inline Mat4x4 Mat4x4::operator-(const Mat4x4& rhs) const
		{
			return Mat4x4(m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2], m[3] - rhs[3],
				m[4] - rhs[4], m[5] - rhs[5], m[6] - rhs[6], m[7] - rhs[7],
				m[8] - rhs[8], m[9] - rhs[9], m[10] - rhs[10], m[11] - rhs[11],
				m[12] - rhs[12], m[13] - rhs[13], m[14] - rhs[14], m[15] - rhs[15]);
		}

		inline Mat4x4& Mat4x4::operator+=(const Mat4x4& rhs)
		{
			m[0] += rhs[0];   m[1] += rhs[1];   m[2] += rhs[2];   m[3] += rhs[3];
			m[4] += rhs[4];   m[5] += rhs[5];   m[6] += rhs[6];   m[7] += rhs[7];
			m[8] += rhs[8];   m[9] += rhs[9];   m[10] += rhs[10];  m[11] += rhs[11];
			m[12] += rhs[12];  m[13] += rhs[13];  m[14] += rhs[14];  m[15] += rhs[15];
			return *this;
		}

		inline Mat4x4& Mat4x4::operator-=(const Mat4x4& rhs)
		{
			m[0] -= rhs[0];   m[1] -= rhs[1];   m[2] -= rhs[2];   m[3] -= rhs[3];
			m[4] -= rhs[4];   m[5] -= rhs[5];   m[6] -= rhs[6];   m[7] -= rhs[7];
			m[8] -= rhs[8];   m[9] -= rhs[9];   m[10] -= rhs[10];  m[11] -= rhs[11];
			m[12] -= rhs[12];  m[13] -= rhs[13];  m[14] -= rhs[14];  m[15] -= rhs[15];
			return *this;
		}

		inline Vector3 Mat4x4::operator*(const Vector3& rhs) const
		{
			return Vector3(m[0] * rhs.x + m[4] * rhs.y + m[8] * rhs.z + m[12],
				m[1] * rhs.x + m[5] * rhs.y + m[9] * rhs.z + m[13],
				m[2] * rhs.x + m[6] * rhs.y + m[10] * rhs.z + m[14]);
		}

		inline Mat4x4 Mat4x4::operator*(const Mat4x4& n) const
		{
			return Mat4x4(m[0] * n[0]  + m[4] * n[1]  + m[8] * n[2]  + m[12] * n[3],  m[1] * n[0]  + m[5] * n[1]  + m[9] * n[2]  + m[13] * n[3],  m[2] * n[0]  + m[6] * n[1]  + m[10] * n[2]  + m[14] * n[3],  m[3] * n[0]  + m[7] * n[1]  + m[11] * n[2]  + m[15] * n[3],
						  m[0] * n[4]  + m[4] * n[5]  + m[8] * n[6]  + m[12] * n[7],  m[1] * n[4]  + m[5] * n[5]  + m[9] * n[6]  + m[13] * n[7],  m[2] * n[4]  + m[6] * n[5]  + m[10] * n[6]  + m[14] * n[7],  m[3] * n[4]  + m[7] * n[5]  + m[11] * n[6]  + m[15] * n[7],
						  m[0] * n[8]  + m[4] * n[9]  + m[8] * n[10] + m[12] * n[11], m[1] * n[8]  + m[5] * n[9]  + m[9] * n[10] + m[13] * n[11], m[2] * n[8]  + m[6] * n[9]  + m[10] * n[10] + m[14] * n[11], m[3] * n[8]  + m[7] * n[9]  + m[11] * n[10] + m[15] * n[11],
						  m[0] * n[12] + m[4] * n[13] + m[8] * n[14] + m[12] * n[15], m[1] * n[12] + m[5] * n[13] + m[9] * n[14] + m[13] * n[15], m[2] * n[12] + m[6] * n[13] + m[10] * n[14] + m[14] * n[15], m[3] * n[12] + m[7] * n[13] + m[11] * n[14] + m[15] * n[15]);
		}

		inline Mat4x4& Mat4x4::operator*=(const Mat4x4& rhs)
		{
			*this = *this * rhs;
			return *this;
		}

		inline bool Mat4x4::operator==(const Mat4x4& n) const
		{
			return (m[0] == n[0]) && (m[1] == n[1]) && (m[2] == n[2]) && (m[3] == n[3]) &&
				(m[4] == n[4]) && (m[5] == n[5]) && (m[6] == n[6]) && (m[7] == n[7]) &&
				(m[8] == n[8]) && (m[9] == n[9]) && (m[10] == n[10]) && (m[11] == n[11]) &&
				(m[12] == n[12]) && (m[13] == n[13]) && (m[14] == n[14]) && (m[15] == n[15]);
		}

		inline bool Mat4x4::operator!=(const Mat4x4& n) const
		{
			return (m[0] != n[0]) || (m[1] != n[1]) || (m[2] != n[2]) || (m[3] != n[3]) ||
				(m[4] != n[4]) || (m[5] != n[5]) || (m[6] != n[6]) || (m[7] != n[7]) ||
				(m[8] != n[8]) || (m[9] != n[9]) || (m[10] != n[10]) || (m[11] != n[11]) ||
				(m[12] != n[12]) || (m[13] != n[13]) || (m[14] != n[14]) || (m[15] != n[15]);
		}

		inline float Mat4x4::operator[](int index) const
		{
			return m[index];
		}

		inline float& Mat4x4::operator[](int index)
		{
			return m[index];
		}

		inline Mat4x4 operator-(const Mat4x4& rhs)
		{
			return Mat4x4(-rhs[0], -rhs[1], -rhs[2], -rhs[3], -rhs[4], -rhs[5], -rhs[6], -rhs[7], -rhs[8], -rhs[9], -rhs[10], -rhs[11], -rhs[12], -rhs[13], -rhs[14], -rhs[15]);
		}

		inline Mat4x4 operator*(float s)
		{
			return Mat4x4(s*m[0], s*m[1], s*m[2], s*m[3], s*m[4], s*m[5], s*m[6], s*m[7], s*m[8], s*m[9], s*m[10], s*m[11], s*m[12], s*m[13], s*m[14], s*m[15]);
		}

		inline Vector3 operator*(const Vector3& v)
		{
			return Vector3(v.x*m[0] + v.y*m[1] + v.z*m[2], v.x*m[4] + v.y*m[5] + v.z*m[6], v.x*m[8] + v.y*m[9] + v.z*m[10]);
		}
	};
