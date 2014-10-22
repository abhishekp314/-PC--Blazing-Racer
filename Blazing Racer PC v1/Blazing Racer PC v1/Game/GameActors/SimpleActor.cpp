#include "stdafx.h"
#include "Game/GameActors/SimpleActor.h"
#include "Graphics/Camera.h"

using namespace Graphics;

extern Camera*		g_pCamera;

SimpleActor::SimpleActor(void)
{
	m_Position	  =XMFLOAT3(0,0,0);
	m_Rotate	  =XMFLOAT3(0,0,0);
	m_Scale		  =XMFLOAT3(1,1,1);
	m_isScrolling = 0;
	m_eActorType=ACTORTYPE_SIMPLE;
}

SimpleActor::SimpleActor(EAssetType _assetType, XMFLOAT3 _pos, XMFLOAT3 _rot, XMFLOAT3 _scale, XMFLOAT4 _color, float _height, float _width, IDirect3DTexture9 *_pTex, float _depth)
{
	m_Position	  = _pos;
	m_Rotate	  = _rot;
	m_Scale		  = _scale;
	m_Color		  = _color;
	m_Width		  =	_width;
	m_Height	  = _height;
	m_pTex		  = _pTex;
	m_Depth		  = _depth;
	m_isScrolling = 0;
	m_eActorType  = ACTORTYPE_SIMPLE;
	m_eAssetType  = _assetType;
}

SimpleActor::~SimpleActor(void)
{

}

void SimpleActor::Init()
{
	m_pSprite=new XSprite();
	m_pSprite->InitSprite(m_Position.x, m_Position.y, m_Height, m_Width, m_pTex, m_Depth, m_isScrolling);
	m_pSprite->SetPosition(m_Position);
	m_pSprite->SetRotation(m_Rotate);
	m_pSprite->SetScale(XMFLOAT3(m_Width, m_Height, 1));
}

void SimpleActor::Update()
{
	m_pSprite->SetScale(XMFLOAT3(m_Width, m_Height, 1));

	m_pSprite->Update();
}

void SimpleActor::Render()
{
	m_pSprite->Render(XGraphics::GetInstance()->GetDevice(),ALP_CUT,g_pCamera->GetViewMat(),g_pCamera->GetProjMat(),m_Color);
}

void SimpleActor::Destroy()
{
	m_pSprite->Destroy();
}