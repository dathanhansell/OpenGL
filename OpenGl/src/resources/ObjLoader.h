#pragma once
#include "stdafx.h"
#include "MGLE.h"
namespace MGLE {
	class Model;
	class ObjLoader
	{
	public:
		Model loadOBJ(std::string File);
	};
}
