#pragma once
#include "Model.h"
#include "tString.h"
namespace MGLE {
	class cModel;
	class ObjLoader {
	public:
		cModel LoadOBJ(tString asFileName);
	};
}
