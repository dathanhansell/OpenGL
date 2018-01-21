#include "Texture.h"

	cTexture::cTexture()
	{
	}

	cTexture::cTexture(tString asFileName)
	{
		LoadFromFile(asFileName);
	}

	cTexture::~cTexture()
	{
	}
	void cTexture::LoadFromFile(tString asFileName) {
		res.LoadFromFile(asFileName);
	}
	void cTexture::Bind() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, res.GetTextureID());
	}
