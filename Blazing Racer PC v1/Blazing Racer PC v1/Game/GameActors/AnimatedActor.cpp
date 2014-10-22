#include "stdafx.h"
#include "Game/GameActors/AnimatedActor.h"
#include "Graphics/Camera.h"

using namespace Graphics;

extern Camera*		g_pCamera;

AnimatedActor::AnimatedActor(void)
{
	m_Position	  = XMFLOAT3(0,0,0);
	m_Rotate	  = XMFLOAT3(0,0,0);
	m_Scale		  = XMFLOAT3(1,1,1);
	m_isScrolling = 0;
	m_eActorType=ACTORTYPE_ANIMATED;
}

AnimatedActor::AnimatedActor(EAssetType _assetType, XMFLOAT3 _pos, XMFLOAT3 _rot, XMFLOAT3 _scale, XMFLOAT4 _color, float _height, float _width, IDirect3DTexture9 *_pTex, float _depth, bool _isScrolling)
{
	m_Position	  = _pos;
	m_Rotate	  = _rot;
	m_Scale		  = _scale;
	m_Color		  = _color;
	m_Width		  = _width;
	m_Height	  = _height;
	m_pTex		  = _pTex;
	m_Depth		  = _depth;
	m_isScrolling = _isScrolling;

	m_eActorType = ACTORTYPE_ANIMATED;
	m_eAssetType = _assetType;
}

AnimatedActor::~AnimatedActor(void)
{
}



void AnimatedActor::Init()
{
	m_pSprite=new XSprite();
	m_pSprite->InitSprite(m_Position.x, m_Position.y, m_Height, m_Width, m_pTex, m_Depth, m_isScrolling);
	m_pSprite->SetPosition(m_Position);
	m_pSprite->SetRotation(m_Rotate);
}

void AnimatedActor::Update()
{
	m_pSprite->SetPosition(m_Position);
	m_pSprite->Update();
}

void AnimatedActor::Render()
{
	m_pSprite->Render(XGraphics::GetInstance()->GetDevice(),TEX_SHADER,g_pCamera->GetViewMat(),g_pCamera->GetProjMat(),m_Color);
}

void AnimatedActor::Destroy()
{
	m_pSprite->Destroy();
}