#pragma once

#ifndef __IACTOR__
#define __IACTOR__

#include "Graphics/XSprite.h"

using namespace Graphics;

class IActor
{
protected:
	XSprite				*m_pSprite;
	XMFLOAT3			m_Position;
	XMFLOAT3			m_Scale;
	XMFLOAT3			m_Rotate;
	XMFLOAT4			m_Color;
	float				m_Width;
	float				m_Height;
	float				m_Depth;
	IDirect3DTexture9	*m_pTex;
	bool				m_isScrolling;
	EActorType			m_eActorType;
	EAssetType			m_eAssetType;

public:
	IActor(void);
	~IActor(void);

	virtual				void Init();
	virtual				void Update();
	virtual				void Render();
	virtual				void Destroy();
	EActorType			GetActorType()						      { return m_eActorType; }
	EAssetType			GetAssetType()							  { return m_eAssetType; }

	void				SetPosition(XMFLOAT3 _newPosition)		  { m_Position  = _newPosition; m_pSprite->SetPosition(m_Position); }
	void				SetRotation(XMFLOAT3 _newRotation)		  { m_Rotate  = _newRotation; }
	void				SetScale(XMFLOAT3 _newScale)			  { m_Scale	 = _newScale; }
	void				SetColor(XMFLOAT4 _newColor)			  { m_Color	 = _newColor; }

	XMFLOAT3			GetPosition()							  { return m_Position; }
	XMFLOAT3			GetRotation()						      { return m_Rotate; }

	XSprite*			GetSprite()								  { return m_pSprite; }

	float				GetHeight()								  { return m_Height; }
	void				SetHeight(float _value)					  { m_Height = _value; }
	float				GetWidth()								  { return m_Width; }
	void				SetWidth(float _value)					  { m_Width = _value; }

};

#endif