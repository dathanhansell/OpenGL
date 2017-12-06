#include "stdafx.h"
#include <gtest\gtest.h>
#include <Vector3.cpp>

TEST(tVector3, Addition)
{
	Vector3 A, B;
	A = { 4,10,6 };
	B = { 5,-2,0 };
	A = A + B;
	EXPECT_EQ(9, A.x);
	EXPECT_EQ(8, A.y);
	EXPECT_EQ(6, A.z);
}



TEST(tVector3, Subtraction)
{
	Vector3 A, B;
	A = { 4,10,6 };
	B = { 5,-2,0 };
	A = A - B;
	EXPECT_EQ(-1, A.x);
	EXPECT_EQ(12, A.y);
	EXPECT_EQ(6, A.z);
}

TEST(tVector3, Multiplication)
{
	Vector3 A, B;
	A = { 4,10,6 };
	B = { 5,-2,0 };
	A = A * B;
	EXPECT_EQ(20, A.x);
	EXPECT_EQ(-20, A.y);
	EXPECT_EQ(0, A.z);
}

TEST(tVector3, Scalar_Multiplication)
{
	Vector3 A;
	float a;
	A = { 4,10,6 };
	a = 5;
	A = A * a;
	EXPECT_EQ(20, A.x);
	EXPECT_EQ(50, A.y);
	EXPECT_EQ(30, A.z);
}

TEST(tVector3, Scalar_Division)
{
	Vector3 A;
	float a;
	A = { 4,10,6 };
	a = 5;
	A = A / a;
	EXPECT_FLOAT_EQ(.8, A.x);
	EXPECT_EQ(2, A.y);
	EXPECT_FLOAT_EQ(1.2, A.z);
	A = { 4,10,6 };
	a = 0;
	A = A / a;
	EXPECT_EQ(4, A.x);
	EXPECT_EQ(10, A.y);
	EXPECT_EQ(6, A.z);
}
TEST(tVector3, Assign_Addition)
{
	Vector3 A, B;
	A = { 4,10,6 };
	B = { 5,-2,0 };
	A += B;
	EXPECT_EQ(9, A.x);
	EXPECT_EQ(8, A.y);
	EXPECT_EQ(6, A.z);
}

TEST(tVector3, Assign_Multiplication)
{
	Vector3 A, B;
	A = { 4,10,6 };
	B = { 5,-2,0 };
	A *= B;
	EXPECT_EQ(20, A.x);
	EXPECT_EQ(-20, A.y);
	EXPECT_EQ(0, A.z);
}

TEST(tVector3, Scalar_Assign_Multiplication)
{
	Vector3 A;
	float a;
	A = { 4,10,6 };
	a = 5;
	A *= a;
	EXPECT_EQ(20, A.x);
	EXPECT_EQ(50, A.y);
	EXPECT_EQ(30, A.z);
}

TEST(tVector3, Unary_Minus)
{
	Vector3 A, B;
	A = { 4,10,6 };
	EXPECT_EQ(-4, -A.x);
	EXPECT_EQ(-10, -A.y);
	EXPECT_EQ(-6, -A.z);
	B = { -5,-15,-0 };
	EXPECT_EQ(5, -B.x);
	EXPECT_EQ(15, -B.y);
	EXPECT_EQ(0, -B.z);
	A += -B;
	EXPECT_EQ(9, A.x);
	EXPECT_EQ(25, A.y);
	EXPECT_EQ(6, A.z);

}