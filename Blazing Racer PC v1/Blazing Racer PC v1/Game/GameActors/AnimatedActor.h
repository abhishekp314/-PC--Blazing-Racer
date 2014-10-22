#pragma once

#ifndef __ANIMATEDACTOR__
#define __ANIMATEDACTOR__

#include "Game/GameActors/iactor.h"
#include "Graphics/XSprite.h"

using namespace Graphics;

class AnimatedActor :
	public IActor
{
	
public:
	AnimatedActor(void);
	AnimatedActor(EAssetType _assetType, XMFLOAT3 _pos, XMFLOAT3 _rot, XMFLOAT3 _scale, XMFLOAT4 _color, float _height, float _width, IDirect3DTexture9 *_pTex, float _depth, bool _isScrolling);
	~AnimatedActor(void);

	void			Init();
	void			Update();
	void			Render();
	void			Destroy();
};

#endif