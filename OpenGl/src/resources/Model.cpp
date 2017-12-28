#include "Model.h"
#include <vector>
#include <map>
#include "Maths.h"
#include "LowLevelSystem.h"
#include "tString.h"
namespace MGLE {

	void cModel::Init() {
		cMeshRes::InitErrorMdl();
	}
	void cModel::LoadFromFile(tString asFileName) {
		//TODO read from filename to get extension and use different loaders depending on extension
		mFileName = asFileName;
		res = new cMeshRes();
		res->LoadOBJFromFile(asFileName);
	}
	void cModel::LoadFromSource(tString asSource) {
		mFileName = "source";
		res = new cMeshRes();
		res->LoadOBJFromSource(asSource);
	}
	cModel::cModel()
	{
		
	}
	cModel::cModel(tString asMisc, int loadType)
	{
		switch (loadType)
		{
		case 0:
			LoadFromFile(asMisc);
			break;
		case 1:
			LoadFromSource(asMisc);
			break;
		default:
			break;
		}
	}
	cModel::~cModel()
	{
		delete res;
	}

	void cModel::Draw() {

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, res->vbo);
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, res->nbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, res->ebo);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		//glDepthMask(GL_TRUE);
		glDrawElements(GL_TRIANGLES,res->mData.indices.size(),GL_UNSIGNED_SHORT,(void*)0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	bool cModel::IsError() {
		return res->mIsError;
	}
}