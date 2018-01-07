#pragma once
#include "TextureRes.h"
namespace MGLE {
	class cTexture
	{
		cTextureRes res;
	public:
		cTexture();
		cTexture(tString asFileName);
		~cTexture();
		void Bind();
		void LoadFromFile(tString asFileName);
	};
}

