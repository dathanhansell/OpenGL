#include "tString.h"
namespace MGLE {


	cString::cString()
	{
	}


	cString::~cString()
	{
	}

	tWString cString::To16(const tString &asString)
	{
		tWString wsTemp;
		size_t needed = mbstowcs(NULL, &asString[0], 0);
		wsTemp.resize(needed);
		mbstowcs(&wsTemp[0], &asString[0], needed);
		return wsTemp;
	}

	tString cString::To8(const tWString &awsString)
	{
		tString sTemp;
		size_t needed = wcstombs(NULL, &awsString[0], 0);
		sTemp.resize(needed);
		wcstombs(&sTemp[0], &awsString[0], needed);
		return sTemp;
	}
}