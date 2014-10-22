#include "stdafx.h"
#include "TextFile.h"

namespace Util
{
	TextFile::TextFile(void)
	{
		m_fileContents = "";
	}

	TextFile::~TextFile(void)
	{

	}

	HRESULT	TextFile::Load(const char *filename)
	{
		fstream fFile;
		fFile.open(filename);

		if(!fFile.good())
		{
			OutputDebugString("Could Not Load File");
			return S_FALSE;
		}

		while(!fFile.eof())
		{
			string tempString;
			getline(fFile,tempString);
			m_fileContents.append(tempString);
		}

		return S_OK;
	}
}