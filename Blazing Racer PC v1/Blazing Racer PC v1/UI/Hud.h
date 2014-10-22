#pragma once

#ifndef __HUD__
#define __HUD__

#include "Graphics/XSprite.h"

using namespace Graphics;

enum EHudAssetType { HUDASSETTYPE_SPEEDOMETER, HUDASSETTYPE_METER_INDICATOR };

const float				MIN_METER_INDICATOR_ANGLE = -1.2;
const float				MAX_METER_INDICATOR_ANGLE = -5;

class Hud
{
	static Hud				*ms_pHud;	
	XMFLOAT3				m_CameraPosition;
	float					m_MeterRotationFactor;
	vector<XSprite*>		m_Sprites;

	Hud()
	{

	}

public:
	~Hud(void);
	void					InitHud(XMFLOAT3 _pos);
	static Hud*				GetInstance();
	void					AddSprite(float _x, float _y, float _width, float _height, char *filename, float _depth, float _isScrollable);
	void					Update();
	void					Render();
	void					SetHudPosition(XMFLOAT3 _Hudpos)		{ m_CameraPosition = _Hudpos;		}
	void					SetMeterRotationFactor(float _angle);
	float					GetMeterRotationFactor()				{ return m_MeterRotationFactor;		}
};

#endif