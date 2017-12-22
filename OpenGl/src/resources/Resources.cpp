#include "Resources.h"
namespace MGLE {
	Resources::Resources() {
		objloader = new ObjLoader();
		mLowLevelSystem = new cLowLevelSystem();

	}
	Resources::~Resources() {
		delete objloader;
		delete mLowLevelSystem;
	}
	GLuint shader;

}