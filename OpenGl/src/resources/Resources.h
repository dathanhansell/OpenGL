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
		
	public:
		Resources();
		~Resources();
		cLowLevelSystem* mLowLevelSystem;
		ObjLoader* objloader;

	};
}
