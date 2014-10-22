#include "stdafx.h"
#include "Hud.h"
#include "Graphics/Camera.h"
#include "Util/Texture.h"
#include "Util/ResourceManager.h"

using namespace Util;
using namespace Graphics;

extern Camera *g_pCamera;

Hud* Hud::ms_pHud = nullptr;

Hud::~Hud(void)
{
}

Hud* Hud::GetInstance()
{
	if(ms_pHud == nullptr)
		ms_pHud = new Hud();
	return ms_pHud;
}

void Hud::InitHud(XMFLOAT3 _pos)
{
	m_CameraPosition = _pos;
	m_MeterRotationFactor = MIN_METER_INDICATOR_ANGLE;
}

void Hud::AddSprite(float _x, float _y, float _width, float _height, char *filename, float _depth, float _isScrollable)
{
	m_Sprites.push_back(new XSprite());

	Texture *pTex = ResourceManager::GetInstance()->Load<Texture>(filename);
	m_Sprites.back()->InitSprite(_x, _y, _width, _height, pTex->GetTexture(), _depth, _isScrollable);
}

void Hud::SetMeterRotationFactor(float _angle)
{
	m_MeterRotationFactor = _angle;

	if(m_MeterRotationFactor > MIN_METER_INDICATOR_ANGLE)
		m_MeterRotationFactor = MIN_METER_INDICATOR_ANGLE;

	if(m_MeterRotationFactor < MAX_METER_INDICATOR_ANGLE)
		m_MeterRotationFactor = MAX_METER_INDICATOR_ANGLE;
}

void Hud::Update()
{
	if(InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_A))
		m_MeterRotationFactor += 0.05;
	if(InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_B))
		m_MeterRotationFactor -= 0.05;

	for(int i=0; i < m_Sprites.size(); i++)
	{
		XMFLOAT3 somPos = m_CameraPosition;
		switch(i)
		{
			case HUDASSETTYPE_SPEEDOMETER:
												somPos = XMFLOAT3(m_CameraPosition.x - SCREEN_WIDTH/2, m_CameraPosition.y - (SCREEN_HEIGHT/2) + 200, 1);
												m_Sprites[i]->SetPosition(somPos);
												m_Sprites[i]->Update();
												break;

			case HUDASSETTYPE_METER_INDICATOR:
												somPos = XMFLOAT3(m_CameraPosition.x - (SCREEN_WIDTH/2) + 96, m_CameraPosition.y - (SCREEN_HEIGHT/2) + 100, 1);
												m_Sprites[i]->SetPosition(somPos);
												//m_rotationFactor = 0;
												m_Sprites[i]->SetRotation(XMFLOAT3(0, 0, m_MeterRotationFactor));
												m_Sprites[i]->Update();
												break;

			default:							break;
		}
	}
}

void Hud::Render()
{
	for(int i=0; i < m_Sprites.size(); i++)
	{
		m_Sprites[i]->Render(XGraphics::GetInstance()->GetDevice(), ALP_CUT, g_pCamera->GetViewMat(), g_pCamera->GetProjMat(), XMFLOAT4(255, 255, 255, 255));
	}
}