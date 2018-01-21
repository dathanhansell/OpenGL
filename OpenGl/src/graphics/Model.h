#pragma once
#include <gl\glew.h>
#include <gl\glut.h>
#include "LowLevelSystem.h"
#include "tString.h"
#include "MeshRes.h"

	class cMeshRes;
	class cModel
	{
		tString mFileName;
		cMeshRes* res;
		void LoadFromSource(tString Name, tString asSource);
		void LoadFromFile(tString Name, tString asFileName);
	public:
#define FROM_FILE  0
#define FROM_SOURCE  1
		static void Init();
		cMeshRes* GetMeshData();
		
		void CreateModel(tString Name, tString asMisc, int createType = 0);
		cModel();
		cModel(tString Name, tString asMisc,int createType = 0);
		~cModel();
		bool IsError();
		void Draw();
	};

