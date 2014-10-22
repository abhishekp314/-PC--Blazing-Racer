#pragma once
#ifndef __X_TEX_SHADER_
#define __X_TEX_SHADER_

#include "Graphics/IShaders.h"
#include "Graphics/XGraphics.h"

namespace Graphics
{
	class XTexShader:public IShaders
	{
		private:

		public:
			XTexShader(void);
			~XTexShader(void);

			HRESULT			InitShader(const char* vertexShader,const char* pixelShader,D3DDevice* pDevice);
			HRESULT			CreateVertBuffer();
			UINT			GetStride() {return sizeof(TEXVERTEX);}

	};


}

#endif
