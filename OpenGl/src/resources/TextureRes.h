#pragma once
#include <gl\glew.h>
#include <gl\glut.h>
#include <vector>
#include <map>
#include "Maths.h"
#include "LowLevelSystem.h"
#include "tString.h"


namespace MGLE {
	class cTextureRes {
		void SetNull();
		GLuint texID;
	public:
		cTextureRes();
		~cTextureRes();
		bool LoadFromFile(tString asFileName);
		bool LoadFromFile(tString XP, tString XN, tString YP, tString YN, tString ZP, tString ZN);
		bool LoadFromFile(tString cubeArray[]);
		GLuint GetTextureID();
	};
}
