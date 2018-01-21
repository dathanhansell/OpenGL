#include "Resources.h"

	Resources::Resources() {

		mLowLevelSystem = new cLowLevelSystem();

	}
	Resources::~Resources() {

		delete mLowLevelSystem;
	}
	GLuint shader;
