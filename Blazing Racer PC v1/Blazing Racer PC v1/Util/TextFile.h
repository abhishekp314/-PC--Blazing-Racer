#pragma once
#ifndef __TEXT_FILE_
#define __TEXT_FILE_


#include <string>
#include <fstream>
#include "IResource.h"

namespace Util
{
	class TextFile:public IResource
	{
	private:
		string		m_fileContents;

	public:
		TextFile(void);
		~TextFile(void);

		HRESULT		Load(const char *filename);
		string		GetFileContents(){return m_fileContents;}
	};
}

#endif
