#include "Cubemap.h"

namespace MGLE {

	cCubemap::cCubemap()
	{
	}


	cCubemap::~cCubemap()
	{
	}

	void cCubemap::LoadFromFile(tString XP, tString XN, tString YP, tString YN, tString ZP, tString ZN) {
		Bar();
		Log("Loading Model From File: XP = %s\n", XP.c_str());
		OpenBar();
		res.LoadFromFile(XP, XN, YP, YN, ZP, ZN);
		Log("Done!\n");
		CloseBar();
	}
	void cCubemap::LoadFromFile(tString cubeArray[]) {
		Bar();
		Log("Loading Model From File: XP = %s\n", cubeArray[0].c_str());
		OpenBar();
		res.LoadFromFile(cubeArray);
		Log("Done!\n");
		CloseBar();
	}
	void cCubemap::Bind() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, res.GetTextureID());
	}
}