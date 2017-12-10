#pragma once
#include <vector>
#include "Maths.h"
#include "Model.h"
class ObjLoader
{
public:
	static Model loadOBJ(const char * File);
};

