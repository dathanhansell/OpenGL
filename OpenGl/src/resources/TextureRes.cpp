#include "TextureRes.h"
#define STB_IMAGE_IMPLEMENTATION    
#include "stb_image.h"
namespace MGLE {
	void cTextureRes::SetNull() {

	}
	cTextureRes::cTextureRes() {

	}
	cTextureRes::~cTextureRes() {

	}
	bool cTextureRes::LoadFromFile(tString asFileName) {
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		int width, height, nrChannels;
		tString path = GetAbsolutePath() + asFileName;
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			Error("Failed to load texture\n");
			return false;
		}

		stbi_image_free(data);
		return true;
	}
	bool cTextureRes::LoadFromFile(tString cubeArray[]) {

		glGenTextures(1, &texID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
		//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
		//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 5);
		char* debug[6]{
			"+x","-x","+y","-y","+z","-z"
		};
		for (int i = 0; i < 6; i++) {
			int width, height, nrChannels;
			tString path = GetAbsolutePath() + cubeArray[i];
			unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					Log("Loaded cubemap segment %s w %i h %i \n", debug[i], width, height);
			}
			else {
				Error("Failed to load cubemap\n");
				return false;
			}
			stbi_image_free(data);
		}
		//glTexParameteri(GL_TEXTURE_BASE_LEVEL,
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		return true;
	}
	bool cTextureRes::LoadFromFile(tString XP, tString XN, tString YP, tString YN, tString ZP, tString ZN) {
		tString files[6]{
			XP,XN,YP,YN,ZP,ZN
		};
		return LoadFromFile(files);
	}
	GLuint cTextureRes::GetTextureID() {
		return texID;
	}
}