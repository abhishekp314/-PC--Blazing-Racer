#pragma once

#ifndef __SIMPLEACTOR__
#define __SIMPLEACTOR__

#include "Game/GameActors/iactor.h"
#include "Graphics/XSprite.h"

using namespace Graphics;

class SimpleActor :public IActor
{
public:
	SimpleActor();
	SimpleActor(EAssetType _assetType, XMFLOAT3 _pos, XMFLOAT3 _rot, XMFLOAT3 _scale, XMFLOAT4 _color, float _height, float _width, IDirect3DTexture9 *_pTex, float _depth);
	~SimpleActor(void);

	void				Init();
	void				Update();
	void				Render();
	void				Destroy();
};

#endif