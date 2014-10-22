#include "StdAfx.h"
#include "Game/GameActors/PhysicsActor.h"
#include "Graphics/Camera.h"
#include "Game/ParticleContact.h"
#include "Sound/XSound/XSound.h"
#include "Util/Texture.h"


using namespace Graphics;
using namespace Util;

extern Camera*		g_pCamera;

PhysicsActor::PhysicsActor()
{
	m_Position			 = XMFLOAT3(0,0,0);
	m_Rotate			 = XMFLOAT3(0,0,0);
	m_Scale				 = XMFLOAT3(1,1,1);
	m_Width				 = 0;
	m_Height			 = 0;
	m_Depth				 = 0;
	m_pTex				 = nullptr;
	m_eActorType		 = ACTORTYPE_PHYSICS;
	m_ePhysicsActorState = PHYSICSACTORSTATE_STOP;
	m_eAssetType		 = ASSETTYPE_NONE;
}

PhysicsActor::PhysicsActor(EAssetType _assetType, XMFLOAT3 _pos, XMFLOAT3 _rot, XMFLOAT3 _scale, XMFLOAT4 _color,float _height, float _width, IDirect3DTexture9 *_pTex, 
							float _depth, XMVECTOR _velocity, XMVECTOR _acceleration, float m_mass, float _damping)
{
	m_Position			 = _pos;
	m_Rotate			 = _rot;
	m_Scale				 = _scale;
	m_Color				 = _color;
	m_Width				 = _width;
	m_Height			 = _height;
	m_pTex				 = _pTex;
	m_Depth				 = _depth;
	m_eActorType		 = ACTORTYPE_PHYSICS;	
	m_eAssetType		 = _assetType;

	m_Position.z		 = _depth;

	m_PhysicsObject = new XPhysics(Float3ToVec(m_Position), _velocity, _acceleration, m_mass, _damping);

	if(m_eAssetType == ASSETTYPE_PLAYER)
	{
#ifdef XBOX
		Texture *tex = ResourceManager::GetInstance()->Load<Texture>("Game:\\Content\\Textures\\nostail.png");
#else
		Texture *tex = ResourceManager::GetInstance()->Load<Texture>("Game:\\Content\\Textures\\nostail.png");
#endif
		m_NOSTailActor = new SimpleActor(ASSETTYPE_NPC, XMFLOAT3(m_Position.x, m_Position.y - _height, m_Position.z), _rot, _scale, _color, 0, 112, tex->GetTexture(), _depth);
	}
}

PhysicsActor::~PhysicsActor(void)
{
}

void PhysicsActor::Init()
{
	m_pSprite = new XSprite();
	m_pSprite->InitSprite(m_Position.x, m_Position.y, m_Height, m_Width, m_pTex, m_Depth, m_isScrolling);
	m_pSprite->SetPosition(m_Position);
	m_pSprite->SetRotation(m_Rotate);
	//m_pSprite->SetScale(m_Scale);

	if(m_eAssetType == ASSETTYPE_PLAYER)
	m_NOSTailActor->Init();

}

void PhysicsActor::Update()
{
	m_PhysicsObject->Integrator();
	m_PhysicsObject->ClearForce();

	SetPosition(VecToFloat3(m_PhysicsObject->GetPosition()));
	m_pSprite->Update();

	if( m_eAssetType == ASSETTYPE_PLAYER || m_eAssetType == ASSETTYPE_NPC || m_eAssetType == ASSETTYPE_PLAYER2)
	{
		//Within Bounds 
		XMVECTOR currPos = m_PhysicsObject->GetPosition();

		if(currPos.x <= -880)
			ParticleContact::GetInstance()->ContactResolve(this->m_PhysicsObject, nullptr, 0.3, 0, Float3ToVec(XMFLOAT3(1, 0, 0)));
		if(currPos.x >= 880)
			ParticleContact::GetInstance()->ContactResolve(this->m_PhysicsObject, nullptr, 1, 0, Float3ToVec(XMFLOAT3(-1, 0, 0)));
	}

	if(m_eAssetType == ASSETTYPE_PLAYER)
	{

		float currNosTailHeight = m_NOSTailActor->GetHeight();

		if (InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_LEFT_SHOULDER))
		{
			if(m_PhysicsObject->GetNOSFill() > 0.0 && currNosTailHeight < 400)
				currNosTailHeight+=5;
			else
				currNosTailHeight -= 10;

			if(currNosTailHeight <= 0)
				currNosTailHeight = 0;
		}
		else
		{

			if(currNosTailHeight <= 0)
				currNosTailHeight = 0;
			else
				currNosTailHeight -= 10;
		}

		m_NOSTailActor->SetHeight(currNosTailHeight);
		m_NOSTailActor->SetPosition(XMFLOAT3(m_Position.x, m_Position.y - m_Height, m_Position.z));

		m_NOSTailActor->Update();
	}
}

void PhysicsActor::Render()
{
	m_pSprite->Render(XGraphics::GetInstance()->GetDevice(), ALP_CUT, g_pCamera->GetViewMat(), g_pCamera->GetProjMat(), m_Color);

	if(m_eAssetType == ASSETTYPE_PLAYER)
		m_NOSTailActor->Render();
}

void PhysicsActor::Destroy()
{

}

QUAD PhysicsActor::GetBoundingBox()
{
	return m_pSprite->GetQuad();
}

void PhysicsActor::OnCollision(PhysicsActor *_otherActor)
{
	SetColor(XMFLOAT4(255,255,255,255));

	EAssetType eCollidedAssetType = _otherActor->GetAssetType();

	switch(eCollidedAssetType)
	{
			case ASSETTYPE_NONE: 
				break;

		
			case ASSETTYPE_PLAYER2:
				if(m_eAssetType == ASSETTYPE_PLAYER)
					XSound::GetInstance()->PlayWave(WAVENAME_CAR_IMPACT_GLASS2, 0, TRUE);
				ParticleContact::GetInstance()->ContactResolve(this->m_PhysicsObject, _otherActor->GetPhysicsObject(), 0.3, 0, this->m_PhysicsObject->GetContactNormal());
				break;

			case ASSETTYPE_ROAD:
				break;

			case ASSETTYPE_ROADBLOCK:
				
				if(m_eAssetType == ASSETTYPE_PLAYER)
					XSound::GetInstance()->PlayWave(WAVENAME_CAR_IMPACT_DASH, 0, TRUE);
				ParticleContact::GetInstance()->ContactResolve(this->m_PhysicsObject, _otherActor->GetPhysicsObject(), 0.3, 0, this->m_PhysicsObject->GetContactNormal());
				break;

			case ASSETTYPE_MUD:
				
				if(m_eAssetType == ASSETTYPE_PLAYER)
					XSound::GetInstance()->PlayWave(WAVENAME_CAR_SKID1, 0, TRUE);
				ParticleContact::GetInstance()->ResolveDragging(this->m_PhysicsObject, _otherActor->GetPhysicsObject(), 1, 0, this->m_PhysicsObject->GetContactNormal());
				break;

			case ASSETTYPE_OIL:
				if(m_eAssetType == ASSETTYPE_PLAYER)
					XSound::GetInstance()->PlayWave(WAVENAME_CAR_SKID2, 0, TRUE);
				ParticleContact::GetInstance()->ResolveDragging(this->m_PhysicsObject, _otherActor->GetPhysicsObject(), 10, 0, Float3ToVec(XMFLOAT3(0.7,0.3,0)));
				break;

			case ASSETTYPE_NPC:
				if(m_eAssetType == ASSETTYPE_PLAYER)
					XSound::GetInstance()->PlayWave(WAVENAME_CAR_IMPACT_GLASS2, 0, TRUE);

				ParticleContact::GetInstance()->ContactResolve(this->m_PhysicsObject, _otherActor->GetPhysicsObject(), 0.3, 0, this->m_PhysicsObject->GetContactNormal());
				break;

			case ASSETTYPE_NOS:
				this->m_PhysicsObject->RefillNOS();
				break;

			case ASSETTYPE_FINISHLINE:
				GameHandler::GetInstance()->SetState(GAMESTATE_GAMEOVER, STATE_DESTROY);

			default:
				break;
	}
}

void PhysicsActor::OnNoCollision()
{

}