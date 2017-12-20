#pragma once
#include "stdafx.h"
#include "MGLE.h"
#include "atlstr.h"
#include "Pathcch.h"
namespace MGLE {
	class ObjLoader;
	class cLowLevelSystem;
	class Resources
	{
		GLuint LoadShaders(std::string vertex_file_path, std::string fragment_file_path);
	public:
		Resources();
		~Resources();
		cLowLevelSystem* mLowLevelSystem;
		ObjLoader* objloader;

	};
}

