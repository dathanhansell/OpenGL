#pragma once
#include <gl\glew.h>
#include <gl\glut.h>
#include "LowLevelSystem.h"
#include "tString.h"
#include "MeshRes.h"
namespace MGLE {
	class cMeshRes;
	class cModel
	{
		tString mFileName;
		cMeshRes* res;
	public:
#define FROM_FILE  0
#define FROM_SOURCE  1
		static void Init();
		cMeshRes* GetMeshData();
		void LoadFromSource(tString asSource);
		void LoadFromFile(tString asFileName);
		cModel();
		cModel(tString asMisc,int loadType= 0);
		~cModel();
		bool IsError();
		void Draw();
	};

}