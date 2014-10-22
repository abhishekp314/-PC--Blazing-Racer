#include "stdafx.h"
#include "Game/GameStates/RunningState.h"
#include "Game/World.h"
#include "Game/GameActors/SimpleActor.h"
#include "Game/LevelLoader.h"
#include "Graphics/Camera.h"
#include "Util/Texture.h"
#include "Util/ResourceManager.h"
#include "Sound/XSound/XSound.h"
#ifdef XBOX
#include "UI/XUserInterface.h"
#endif
#include "UI/Hud.h"
#include "Network/NetworkManager.h"

using namespace GameState;
using namespace Graphics;
using namespace Util;

extern Camera*		g_pCamera;
extern TimeInfo		g_Time;


RunningState::RunningState(void)
{
	m_isPaused	 = false;
}

RunningState::~RunningState(void)
{
	World::GetInstance()->Destroy();
}

void RunningState::Init()
{
	int initialX=-400;
	int distanceBetween = 200;

	m_GameMode = GameHandler::GetInstance()->GetCurrentGameMode();
#ifdef XBOX
	LevelLoader::GetInstance()->LoadLevel("Game:\\Content\\Levels\\Level1.txt");
	Texture*	pTex = ResourceManager::GetInstance()->Load<Texture>("Game:\\Content\\Textures\\car.png");
#else
	LevelLoader::GetInstance()->LoadLevel("Content\\Levels\\Level1.txt");
	Texture*	pTex = ResourceManager::GetInstance()->Load<Texture>("Content\\Textures\\car.png");
#endif

	if(m_GameMode == GAMEMODE_SINGLEPLAYER)
	{
		m_LocalPlayerIndex = 0;
		Car* tempCar=new Car();
		tempCar->SpawnCar(0, XMFLOAT3(initialX, 150, 0), XMFLOAT3(0,0,0), 227, 125, pTex->GetTexture(), 1);
		m_PlayerList.push_back(tempCar);
	}
	else
		m_LocalPlayerIndex = NetworkManager::getInstance()->GetLocalPlayerIndex();

	for(int i=0; i< NetworkManager::getInstance()->GetNumberOfPlayers(); i++)
	{
		Car* tempCar=new Car();
		tempCar->SpawnCar(0, XMFLOAT3(initialX+distanceBetween*i, 150, 0), XMFLOAT3(0,0,0), 227, 125, pTex->GetTexture(), 1);
		m_PlayerList.push_back(tempCar);
	}

	World::GetInstance()->Init();

	Hud::GetInstance()->InitHud(g_pCamera->GetCameraPosition());
#ifdef XBOX
	Hud::GetInstance()->AddSprite(0, 0, 200, 200, "Game:\\Content\\textures\\speedometer.png", 1, false);
	Hud::GetInstance()->AddSprite(0, 0, 65, 5, "Game:\\Content\\Textures\\meterdetecter.png", 1, false);
#else
	Hud::GetInstance()->AddSprite(0, 0, 200, 200, "Content\\textures\\speedometer.png", 1, false);
	Hud::GetInstance()->AddSprite(0, 0, 65, 5, "Content\\Textures\\meterdetecter.png", 1, false);
#endif

	m_pitchLevel = 0;
	XSound::GetInstance()->PlayWave(WAVENAME_CAR_ENGINE_IDLE, m_pitchLevel, FALSE);

}


void RunningState::Update()
{
	XSound::GetInstance()->PlayWave(WAVENAME_CAR_ENGINE_IDLE, m_pitchLevel, FALSE);

	//Get Handle on Player 1 from World always the last asset loaded from the level loader, instance id = Last Actor
	//m_pPlayer1		= static_cast <PhysicsActor*> (World::GetInstance()->GetActor(World::GetInstance()->GetNumOfActors()-1));

	//Get Handle on Player 2 from World always the last second asset loaded from the level loader, instance id = Last Second Actor
	//Player 2 will be mapped based on Network input from the Other client side
	//m_pPlayer2		= static_cast <PhysicsActor*> (World::GetInstance()->GetActor(World::GetInstance()->GetNumOfActors()-2));

	//Get Handle on Background Scrolling Assets from World always the first asset loaded from the level loader, from instance id = 1 onwards
	m_pAnimatedRoad = static_cast <AnimatedActor*>(World::GetInstance()->GetActor(0));


	XMFLOAT3 temp = m_PlayerList[m_LocalPlayerIndex]->GetPhysicsActor()->GetPosition();
	m_PlayerList[m_LocalPlayerIndex]->SetInput(InputManager::GetInstance()->GetInput());
	m_PlayerList[m_LocalPlayerIndex]->Update();

	//Set Background scrolling parameters
	m_pAnimatedRoad->SetPosition(	XMFLOAT3(m_pAnimatedRoad->GetPosition().x, 
											 m_PlayerList[m_LocalPlayerIndex]->GetPhysicsActor()->GetPosition().y + 360 + CameraOffsetYPositionRelativeToPlayer , 
											 m_pAnimatedRoad->GetPosition().z));

	m_pAnimatedRoad->GetSprite()->UpdateScroll(m_PlayerList[m_LocalPlayerIndex]->GetPhysicsActor()->GetPosition());

	//Check the collisions within the world
	World::GetInstance()->CheckAllCollisions();
	World::GetInstance()->Update();

	
	XMFLOAT2 leftThumbXY = InputManager::GetInstance()->GetLeftThumbStickValue();

	if(InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_START))
	{
		XSound::GetInstance()->PlayWave(WAVENAME_MENU_SCROLL_BLIP, 0, TRUE);
		m_isPaused = TRUE;
		GameHandler::GetInstance()->SetState(GAMESTATE_PAUSE, STATE_STORE);
	}
	
	
	g_pCamera->SetTarget(	XMFLOAT3(m_PlayerList[m_LocalPlayerIndex]->GetPhysicsActor()->GetPosition().x, 
									 m_PlayerList[m_LocalPlayerIndex]->GetPhysicsActor()->GetPosition().y + CameraOffsetYPositionRelativeToPlayer, 
									 m_PlayerList[m_LocalPlayerIndex]->GetPhysicsActor()->GetPosition().z), 1);


	Hud::GetInstance()->SetHudPosition(g_pCamera->GetCameraPosition());
	Hud::GetInstance()->Update();
}

void RunningState::Render()
{
	XGraphics::GetInstance()->GetDevice()->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0,0,0), 1.0f, 0L );
	World::GetInstance()->Render();
	Hud::GetInstance()->Render();
}

void RunningState::Destroy()
{
	World::GetInstance()->Destroy();
}