#pragma once
#include <string>
namespace MGLE {
	
	typedef std::string tString;
	typedef std::wstring tWString;
	class cString
	{
	public:
		static tWString To16(const tString &asString);
		static tString To8(const tWString &awsString);
		cString();
		~cString();
	};
}
