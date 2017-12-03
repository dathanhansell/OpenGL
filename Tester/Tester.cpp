
#include "stdafx.h"

#include <gtest\gtest.h>
void main(int argc, char* argv[])
{
	int stop;
	testing::InitGoogleTest(&argc,argv);
	RUN_ALL_TESTS();
	std::cin >> stop;
}

