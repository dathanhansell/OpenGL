#pragma once
#include "TextureRes.h"
namespace MGLE {
	class cCubemap
	{
		cTextureRes res;
	public:
		cCubemap();
		~cCubemap();
		void LoadFromFile(tString XP, tString XN, tString YP, tString YN, tString ZP, tString ZN);
		void LoadFromFile(tString cubeArray[]);
		void Bind();
	};
}

