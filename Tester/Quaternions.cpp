#include "stdafx.h"
#include <gtest\gtest.h>
#include <Maths.h>

TEST(Quaternions, QuatRotation)
{
	Quaternion A;
	A.Rotate(30, 60, 90);
	EXPECT_EQ(0.5, A.x);
	EXPECT_TRUE(A.x == .5f);
}