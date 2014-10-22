// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifndef WIN32
#define WIN32
#endif

enum EGameState					{ GAMESTATE_INTRO, GAMESTATE_MAINMENU, GAMESTATE_NEWGAME, GAMESTATE_CONNECTION, GAMESTATE_CONNECTIONSTATE_SERVER, GAMESTATE_CONNECTIONSTATE_CLIENT, 
								  GAMESTATE_RUNNING, GAMESTATE_PAUSE, GAMESTATE_GAMEOVER, GAMESTATE_END};

enum EWhatToDoWithPreviousState	{ STATE_STORE, STATE_DESTROY, STATE_NONE};

enum EActorType					{ ACTORTYPE_SIMPLE, ACTORTYPE_ANIMATED, ACTORTYPE_PHYSICS};

enum EPhysicsActorState			{ PHYSICSACTORSTATE_MOVINGFORWARD, PHYSICSACTORSTATE_MOVINGREVERSE, PHYSICSACTORSTATE_MOVINGRIGHT, PHYSICSACTORSTATE_MOVINGLEFT, 
								  PHYSICSACTORSTATE_STOP };

enum EAssetType					{ ASSETTYPE_NONE, ASSETTYPE_PLAYER, ASSETTYPE_PLAYER2, ASSETTYPE_ROAD, ASSETTYPE_ROADBLOCK, ASSETTYPE_MUD, ASSETTYPE_OIL, ASSETTYPE_NPC, ASSETTYPE_NOS , ASSETTYPE_FINISHLINE};

enum EConnectionType			{ CONNECTIONTYPE_SERVER, CONNECTIONTYPE_CLIENT, CONNECTIONTYPE_NONE };

enum EGameMode					{ GAMEMODE_SINGLEPLAYER, GAMEMODE_MULTIPLAYER };

const float						CameraOffsetYPositionRelativeToPlayer = 100;

const float						SCREEN_WIDTH  = 1280;
const float						SCREEN_HEIGHT = 720;

#ifdef XBOX
#include <xtl.h>
#include <xui.h>
#include <xboxmath.h>
#endif

#ifdef WIN32
#include <WinSock2.h>
#include <Windows.h>
#include <DxErr.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <Xinput.h>

#define _XM_NO_INTRINSICS_
#include <xnamath.h>
#include <xnamathvector.inl>

#define D3DDevice IDirect3DDevice9
#define Direct3D  IDirect3D9
#define D3DVertexShader IDirect3DVertexShader9
#define D3DPixelShader  IDirect3DPixelShader9
#define D3DVertexDeclaration IDirect3DVertexDeclaration9
#define D3DVertexBuffer IDirect3DVertexBuffer9
#endif

#include "Graphics/XGraphics.h"
#include "Input/InputManager.h"
#include "Game/GameHandler.h"



// TODO: reference additional headers your program requires here
