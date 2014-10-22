#include "stdafx.h"
#include "XShader.h"

using namespace std;

namespace Graphics
{
	XShader::XShader(void)
	{
		m_pVertexShader	= nullptr;
		m_pPixelShader	= nullptr;
		m_pVertDec		= nullptr;
	}


	XShader::~XShader(void)
	{
		m_pVertexShader->Release();
		m_pPixelShader->Release();
	}


	HRESULT XShader:: InitShader(const char* vertexShader,const char* pixelShader,D3DDevice *pDevice)
	{
		//-------------------------------------------------------------------------------------
		// Vertex shader
		//-------------------------------------------------------------------------------------
		OutputDebugString("Came");
		/*
		strVertexShaderProgram = 
			" float4x4 matWVP : register(c0);              "  
			"                                              "  
			" struct VS_IN                                 "  
			" {                                            " 
			"     float4 ObjPos   : POSITION;              "  // Object space position 
			"     float4 Color    : COLOR;                 "  // Vertex color                 
			" };                                           " 
			"                                              " 
			" struct VS_OUT                                " 
			" {                                            " 
			"     float4 ProjPos  : POSITION;              "  // Projected space position 
			"     float4 Color    : COLOR;                 "  
			" };                                           "  
			"                                              "  
			" VS_OUT main( VS_IN In )                      "  
			" {                                            "  
			"     VS_OUT Out;                              "  
			"     Out.ProjPos = mul( matWVP, In.ObjPos );  "  // Transform vertex into
			"     Out.Color = In.Color;                    "  // Projected space and 
			"     return Out;                              "  // Transfer color
			" }                                            ";

		//-------------------------------------------------------------------------------------
		// Pixel shader
		//-------------------------------------------------------------------------------------
		strPixelShaderProgram = 
			" float4 color : register(c2);					"  
			" struct PS_IN                                 "
			" {                                            "
			"     float4 Color : COLOR;                    "  // Interpolated color from                      
			" };                                           "  // the vertex shader
			"                                              "  
			" float4 main( PS_IN In ) : COLOR              "  
			" {                                            "  
			"     return color;								"  // Output color
			" }                                            "; 
		//////Temp Strings Need to change after resource loading is done !
		*/

		TextFile *vert, *pix;
		vert = ResourceManager::GetInstance()->Load<TextFile>(vertexShader);
		pix = ResourceManager::GetInstance()->Load<TextFile>(pixelShader);
		string ver, pixe;
		a = 10;
		ver = vert->GetFileContents();
		pixe = pix->GetFileContents();
		
		ID3DXBuffer* pVertexShaderCode;
		ID3DXBuffer* pVertexErrorMessage;

		//Creating Vertex Shader
		HRESULT hr = D3DXCompileShader(ver.c_str(),(UINT)strlen(ver.c_str()),NULL,NULL,"main","vs_2_0",0,&pVertexShaderCode,&pVertexErrorMessage,NULL);

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
		hr = D3DXCompileShader(pixe.c_str(),(UINT)strlen(pixe.c_str()),NULL,NULL,"main","ps_2_0",0,&pPixelShaderCode,&pPixelErrorMessage,NULL);

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
			{ 0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
			D3DDECL_END()
		};

		pDevice->CreateVertexDeclaration(VertexElements,&m_pVertDec);

		return S_OK;
	}
}
