#include "Resources.h"

Resources::Resources() {
	objloader = new ObjLoader();
}
Resources::~Resources() {
	delete objloader;
}