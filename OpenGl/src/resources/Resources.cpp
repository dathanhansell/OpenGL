#include "Resources.h"
namespace MGLE {
	Resources::Resources() {

		mLowLevelSystem = new cLowLevelSystem();

	}
	Resources::~Resources() {

		delete mLowLevelSystem;
	}
	GLuint shader;

}