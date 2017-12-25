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
		cMeshRes* GetMeshData();
		void LoadFromFile(tString asFileName);
		cModel();
		cModel(tString asFileName);
		~cModel();
		void Draw();
	};

}