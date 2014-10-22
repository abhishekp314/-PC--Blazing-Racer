#include "stdafx.h"
#include "Texture.h"

namespace Util
{

	Texture::Texture(void)
	{
		m_pTexture=NULL;
	}


	Texture::~Texture(void)
	{
	}

	HRESULT Texture::Load(const char* filename)
	{
		if(FAILED(D3DXCreateTextureFromFile(XGraphics::GetInstance()->GetDevice(),filename,&m_pTexture)))
		{
			return E_FAIL;
		}

		return S_OK; 
	}


	IDirect3DTexture9* Texture::GetTexture()
	{
		return m_pTexture;
	}
}
