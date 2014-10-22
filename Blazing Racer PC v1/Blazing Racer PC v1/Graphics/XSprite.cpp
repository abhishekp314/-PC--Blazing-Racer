#include "stdafx.h"
#include "XSprite.h"

namespace Graphics
{
	XSprite::XSprite(void)
	{
		m_pSpriteTexture	= nullptr;
		m_bScrolling		= false;
		m_vScrolling		= XMFLOAT3(0,0,0);
		m_vYaw.x			= 0.0f;
		m_vYaw.y			= 0.0f;
		m_vYaw.z			= 1.0f;
		m_vYaw.w			= 0.0f;
							  
		m_mRot				= XMMatrixIdentity();
		m_mTrans			= XMMatrixIdentity();
	}


	XSprite::~XSprite(void)
	{
	}


	bool XSprite::InitSprite(float posX,float posY,float height,float width,IDirect3DTexture9* pTexture,float depth,bool bScrolling)
	{
		m_pSpriteTexture	= pTexture;

		m_bScrolling		= bScrolling;

		m_vPosition.x		= posX;
		m_vPosition.y		= posY;
		m_vPosition.z		= depth;

		m_vScaling.x		= width;
		m_vScaling.y		= height;
		m_vScaling.z		= depth;
		
 		m_Width				=width;
 		m_Height			=height;	
 		m_Depth				=depth;

		m_WorldMat			= XMMatrixIdentity();

		m_qQuad.a			= XMFLOAT3(posX,posY,depth);
		m_qQuad.b			= XMFLOAT3(posX,posY-height,depth);
		m_qQuad.c			= XMFLOAT3(posX+width,posY-height,depth);
		m_qQuad.d			= XMFLOAT3(posX+width,posY,depth);
		m_qQuad.width		= m_Width;
		m_qQuad.height		= m_Height;

		m_pSpriteTexture	= pTexture;

		return true;		//ErrorCheck this !
	}

	void XSprite::UpdateScroll(XMFLOAT3 scrolling)	
	{
		if(m_bScrolling)
		{
			XMVECTOR currScrollPosition;
			currScrollPosition.x  = 0;
			currScrollPosition.y  = -scrolling.y/720;
			currScrollPosition.z  = 1;
			m_vScrolling = VecToFloat3(currScrollPosition);
		}
	}

	void XSprite::Update()
	{
		XMMATRIX scaleMat	= XMMatrixScaling(m_vScaling.x,m_vScaling.y,m_vScaling.z);
		XMMATRIX transMat	= XMMatrixTranslation(m_vPosition.x,m_vPosition.y,m_vPosition.z);		
		XMMATRIX rotMat = XMMatrixIdentity();
		m_WorldMat			= scaleMat*rotMat*transMat;

	}

	void XSprite::Render(D3DDevice* pDevice, eSHADERS Shader,XMMATRIX viewMat,XMMATRIX projMat,XMFLOAT4 spriteColor)
	{
		XMFLOAT4 color = spriteColor;
		IShaders *pShader	= XGraphics::GetInstance()->GetShader(Shader);

		pDevice->BeginScene();

		pDevice->SetVertexDeclaration(pShader->GetVertexDec());
		pDevice->SetStreamSource(0,pShader->GetVertexBuffer(),0,pShader->GetStride());
		pDevice->SetVertexShader(pShader->GetVertexShader());
		pDevice->SetPixelShader(pShader->GetPixelShader());
		
		pDevice->SetTexture(0,m_pSpriteTexture);

		// Texture stage states
		//pDevice->SetBlendState(0,sj->GetBlState());


		
		
		if(Shader == ALP_CUT)
		{
			pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

			pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
			//pDevice->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ZERO);
			//pDevice->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ZERO);



			pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			
		}
		
		pDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC );
		

		XMMATRIX matWVP = m_WorldMat*viewMat*projMat;//Multiply view and projection matrix !
		pDevice->SetVertexShaderConstantF(0,(FLOAT*)&matWVP,4);
		pDevice->SetVertexShaderConstantF(4,(FLOAT*)&m_vScrolling,1);

		pDevice->SetPixelShaderConstantF(2,(FLOAT*)&color,1);

		HRESULT hr;
		if (hr = pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2))
		{
			char str[2048];
			sprintf(str, "Error: %s Desc: %s \n", DXGetErrorString(hr), DXGetErrorDescription(hr));
			OutputDebugString(str);
		}
		pDevice->EndScene();
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	}	

	void XSprite::Destroy()
	{
		m_pSpriteTexture->Release();
		//SAFE_DELETE_POINTER(m_pSpriteTexture);
	}


}

