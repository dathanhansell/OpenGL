#include "stdafx.h"
#include <gtest\gtest.h>
#include <Quaternion.cpp>

TEST(tQuaternion, Rotation_Identity)
{
	Quaternion A;
	A.Rotate(0, 0, 0);
	EXPECT_EQ(0, A.x);
	EXPECT_EQ(0, A.y);
	EXPECT_EQ(0, A.z);
	EXPECT_EQ(1, A.w);
}

TEST(tQuaternion, Rotation_OneAxis)
{
	Quaternion A;
	A.Rotate(30, 0, 0);
	EXPECT_NEAR(0.258819, A.x, .000001);
	EXPECT_EQ(0, A.y);
	EXPECT_EQ(0, A.z);
	EXPECT_NEAR(0.9659258, A.w, .000001);

	A.Rotate(0, 124, 0);
	EXPECT_EQ(0, A.x);
	EXPECT_NEAR(0.8829476, A.y, .000001);
	EXPECT_EQ(0, A.z);
	EXPECT_NEAR(0.4694716, A.w, .000001);

	A.Rotate(0, 0, 280);
	EXPECT_EQ(0, A.x);
	EXPECT_EQ(0, A.y);
	EXPECT_NEAR(0.6427876, A.z, .000001);
	EXPECT_NEAR(-0.7660444, A.w, .000001);

}

TEST(tQuaternion, Rotation_MultiAxis)
{
	Quaternion A;
	A.Rotate(30, 60, 90);
	EXPECT_NEAR(0.5000000, A.x, .000001);
	EXPECT_NEAR(0.1830127, A.y, .000001);
	EXPECT_NEAR(0.4999999, A.z, .000001);
	EXPECT_NEAR(0.6830127, A.w, .000001);

	A.Rotate(250, 124, 135);
	EXPECT_NEAR(-0.3207196, A.x, .000001);
	EXPECT_NEAR(-0.5491005, A.y, .000001);
	EXPECT_NEAR(-0.5255631, A.z, .000001);
	EXPECT_NEAR( 0.5651646, A.w, .000001);

	A.Rotate(52, 73, 32);
	EXPECT_NEAR(0.4860989, A.x, .000001);
	EXPECT_NEAR(0.4167815, A.y, .000001);
	EXPECT_NEAR(-0.05150352, A.z, .000001);
	EXPECT_NEAR(0.7663866, A.w, .000001);

}

TEST(tQuaternion, ToEulerAngles)
{
	Quaternion A;
	Vector3 E;
	A.Rotate(30, 60, 90);
	EXPECT_NEAR(0.5000000, A.x, .000001);
	EXPECT_NEAR(0.1830127, A.y, .000001);
	EXPECT_NEAR(0.4999999, A.z, .000001);
	EXPECT_NEAR(0.6830127, A.w, .000001);

	E = A.ToEuler();
	EXPECT_EQ(30, E.x);
	EXPECT_EQ(60, E.y);
	EXPECT_EQ(90, E.z);

	A.Rotate(250, 124, 135);
	EXPECT_NEAR(-0.3207196, A.x, .000001);
	EXPECT_NEAR(-0.5491005, A.y, .000001);
	EXPECT_NEAR(-0.5255631, A.z, .000001);
	EXPECT_NEAR(0.5651646, A.w, .000001);

	E = A.ToEuler();
	EXPECT_EQ(250, E.x);
	EXPECT_EQ(124, E.y);
	EXPECT_EQ(135, E.z);

	A.Rotate(52, 73, 32);
	EXPECT_NEAR(0.4860989, A.x, .000001);
	EXPECT_NEAR(0.4167815, A.y, .000001);
	EXPECT_NEAR(-0.05150352, A.z, .000001);
	EXPECT_NEAR(0.7663866, A.w, .000001);

	E = A.ToEuler();
	EXPECT_EQ(52, E.x);
	EXPECT_EQ(73, E.y);
	EXPECT_EQ(32, E.z);

}