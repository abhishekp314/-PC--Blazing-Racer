#pragma once
#include "stdafx.h"
#include "Graphics/XGraphics.h"
#include "IResource.h"
#include <string>
#ifndef __TEXTURE_
#define __TEXTURE_

using namespace Graphics;

namespace Util
{
	class Texture:public IResource
	{
		IDirect3DTexture9* m_pTexture;

	public:
		Texture(void);
		~Texture(void);

		HRESULT Load(const char* filename);

		IDirect3DTexture9* GetTexture();
	};

}

#endif

