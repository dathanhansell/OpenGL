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
	void cModel::LoadFromFile(tString Name, tString asFileName) {
		//TODO read from filename to get extension and use different loaders depending on extension
		mFileName = Name;
		res = new cMeshRes();
		res->LoadOBJFromFile(asFileName);
	}
	void cModel::LoadFromSource(tString Name, tString asSource) {
		mFileName = Name;
		res = new cMeshRes();
		res->LoadOBJFromSource(asSource);
	}
	cModel::cModel()
	{
		
	}
	cModel::cModel(tString Name,tString asMisc, int createType)
	{
		CreateModel(Name,asMisc,createType);
	}
	void cModel::CreateModel(tString Name, tString asMisc, int createType) {
		switch (createType)
		{
		case 0:
			Bar();
			Log("Loading Model From File: %s\n", asMisc.c_str());
			OpenBar();
			LoadFromFile(Name, asMisc);
			break;
		case 1:
			Bar();
			Log("Loading Model From Source: %s\n", asMisc.c_str());
			OpenBar();
			LoadFromSource(Name, asMisc);
			break;
		default:
			break;
		}
		CloseBar();
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

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, res->tbo);
		
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, res->ebo);
		glEnable(GL_CULL_FACE);
		
		//glDepthMask(GL_TRUE);
		glDrawElements(GL_TRIANGLES,res->mData.indices.size(),GL_UNSIGNED_SHORT,(void*)0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	bool cModel::IsError() {
		return res->mIsError;
	}
}