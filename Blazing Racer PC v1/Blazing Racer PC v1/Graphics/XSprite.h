#pragma once
#ifndef __SPRITE_
#define __SPRITE_

#include "Util/Util.h"
#include "Graphics/XGraphics.h"

using namespace Util;

namespace Graphics
{
	class XSprite
	{
	private:
		XMVECTOR m_vYaw;
		XMFLOAT3			m_vPosition,m_vRotation,m_vScaling;
		XMFLOAT3			m_vScrolling;
		IDirect3DTexture9*	m_pSpriteTexture;
		QUAD				m_qQuad;
		XMMATRIX			m_WorldMat;

		XMMATRIX			m_mTrans;
		XMMATRIX			m_mRot;
 		float				m_Width;
 		float				m_Height;
 		float				m_Depth;
		bool				m_bScrolling;

	public:
		XSprite(void);
		~XSprite(void);

		bool				InitSprite(float posX, float posY,float height,float width,IDirect3DTexture9* tex,float depth,bool bScrollable);
		void				Update();
		void				Render(D3DDevice* pDevice,eSHADERS Shader,XMMATRIX viewMat,XMMATRIX projMat,XMFLOAT4 spriteColor);
		void				Destroy();
		void				SetPosition(XMFLOAT3 newPosition)	{m_vPosition	= newPosition;}

		void				SetRotation(XMFLOAT3 newRotation)	{m_vRotation = newRotation;}
		void				SetScale(XMFLOAT3 newScale)			{m_vScaling	 = newScale; m_Width=newScale.x; m_Height=newScale.y;}
		void				UpdateScroll(XMFLOAT3 scrolling);

		XMFLOAT3			GetPosition()						{return m_vPosition;}
		XMFLOAT3			GetRotation()						{return m_vRotation;}
		QUAD				GetQuad()							{
																	m_qQuad.a		= m_vPosition;
																	m_qQuad.b		= XMFLOAT3(m_vPosition.x+m_Width,m_vPosition.y,m_Depth);
			 														m_qQuad.c		= XMFLOAT3(m_vPosition.x,m_vPosition.y-m_Height,m_Depth);
																	m_qQuad.d		= XMFLOAT3(m_vPosition.x+m_Width,m_vPosition.y-m_Height,m_Depth);
																	m_qQuad.width	= m_Width;
																	m_qQuad.height	= m_Height;
																	return m_qQuad;
																}
		XMMATRIX			GetWorldMatrix()					{return m_WorldMat;}
	};


}

#endif

