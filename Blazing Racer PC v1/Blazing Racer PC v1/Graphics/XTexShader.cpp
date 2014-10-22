#include "stdafx.h"
#include "XTexShader.h"

namespace Graphics
{
	
	XTexShader::XTexShader(void)
	{
		m_pVertexShader	= nullptr;
		m_pPixelShader	= nullptr;
		m_pVertDec		= nullptr;
		m_pVertexBuffer = nullptr;
	}


	XTexShader::~XTexShader(void)
	{
		m_pVertexShader->Release();
		m_pPixelShader->Release();
	}


	HRESULT XTexShader:: InitShader(const char* vertexShader,const char* pixelShader,D3DDevice *pDevice)
	{
		//-------------------------------------------------------------------------------------
		// Vertex Shader and Pixel Shader
		//-------------------------------------------------------------------------------------

		TextFile *vert,*pix;
		vert =  ResourceManager::GetInstance()->Load<TextFile>(vertexShader);
		pix  =  ResourceManager::GetInstance()->Load<TextFile>(pixelShader);

		string sVert,sPix;
		sVert = vert->GetFileContents();
		sPix = pix->GetFileContents();

		ID3DXBuffer* pVertexShaderCode;
		ID3DXBuffer* pVertexErrorMessage;


		//Creating Vertex Shader
		HRESULT hr = D3DXCompileShader(sVert.c_str(),strlen(sVert.c_str()),NULL,NULL,"main","vs_2_0",0,&pVertexShaderCode,&pVertexErrorMessage,NULL);

		if(FAILED(hr))
		{
			if(pVertexErrorMessage)
				OutputDebugString((char*)pVertexErrorMessage->GetBufferPointer());
			return E_FAIL;
		}
		pDevice->CreateVertexShader((DWORD*)pVertexShaderCode->GetBufferPointer(),&m_pVertexShader);

		ID3DXBuffer* pPixelShaderCode;
		ID3DXBuffer* pPixelErrorMessage;

		//Creating Pixel Shader
		hr = D3DXCompileShader(sPix.c_str(),strlen(sPix.c_str()),NULL,NULL,"main","ps_2_0",0,&pPixelShaderCode,&pPixelErrorMessage,NULL);

		if(FAILED(hr))
		{
			if(pPixelErrorMessage)
				OutputDebugString((char*)pPixelErrorMessage->GetBufferPointer());
			return E_FAIL;
		}
		pDevice->CreatePixelShader((DWORD*)pPixelShaderCode->GetBufferPointer(),&m_pPixelShader);

		//Creating Vertex Declaration
		D3DVERTEXELEMENT9 VertexElements[3]=
		{
			{ 0, 0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
			{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			D3DDECL_END()
		};

		if (FAILED(pDevice->CreateVertexDeclaration(VertexElements, &m_pVertDec)))
			return S_FALSE;


		if(FAILED(CreateVertBuffer()))
			return S_FALSE;


		return S_OK;
	}

	HRESULT XTexShader::CreateVertBuffer()
	{

		if(FAILED(XGraphics::GetInstance()->GetDevice()->CreateVertexBuffer(6*sizeof(TEXVERTEX),D3DUSAGE_WRITEONLY,NULL,D3DPOOL_MANAGED,&m_pVertexBuffer,NULL)))//Creating the Vertex Buffer
			return E_FAIL;


		TEXVERTEX Vertices[] = 
		{
			{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
			{ 1.0f, 0.0f, 0.0f, 1.0f, 0.0f},
			{ 0.0f, -1.0f, 0.0f, 0.0f, 1.0f}, // x, y, z, color


			{ 0.0f, -1.0f, 0.0f, 0.0f, 1.0f},
			{ 1.0f, 0.0f, 0.0f, 1.0f, 0.0f},
			{ 1.0f, -1.0f, 0.0f, 1.0f, 1.0f} // x, y, z, color
		};

		TEXVERTEX* pVertices;

		if( FAILED( m_pVertexBuffer->Lock( 0, 0, (void**)&pVertices,  0) ) )
			return E_FAIL;

		memcpy( pVertices, Vertices, 6*sizeof(TEXVERTEX) );
		m_pVertexBuffer->Unlock();

		return S_OK;
	}
}

