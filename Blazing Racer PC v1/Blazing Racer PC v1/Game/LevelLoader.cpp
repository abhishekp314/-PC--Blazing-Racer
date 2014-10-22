#include "stdafx.h"
#include "LevelLoader.h"
#include "Game/GameActors/PhysicsActor.h"
#include "Game/GameActors/SimpleActor.h"
#include "Game/World.h"
#include "Util/ResourceManager.h"
#include "Util/Texture.h"

using namespace Util;

LevelLoader* LevelLoader::ms_pLevelLoader=nullptr;

LevelLoader::~LevelLoader(void)
{
}

LevelLoader* LevelLoader::GetInstance()
{
	if(ms_pLevelLoader==nullptr)
		ms_pLevelLoader=new LevelLoader();
	return ms_pLevelLoader;
}

void LevelLoader::LoadLevel(char *_pLevelFilename)
{
	XMFLOAT3	pos,rot,scale;
	float		width,height,zIndex;
	XMFLOAT4	color;
	int			actorType=0;
	char		pTextureName[256];
	Texture		*pTex;
	IActor		*pActorToAdd = nullptr;
	char		textureAbsolutePath[1024];
	int			scroll = 0;
	EAssetType	eAssetType = ASSETTYPE_NONE;

	//Scaling is not required for now, Initialize to (1,1,1) for all assets
	scale = XMFLOAT3(1, 1, 1);

	FILE *fp;
	fp=fopen(_pLevelFilename,"r");

	int res=0;
	while(true)
	{
		pActorToAdd = nullptr;
		res=fscanf(fp,"%d %d %f %f %f  %f %f %f  %f %f %f %f  %f %f  %s  %f",&actorType, &eAssetType, &pos.x, &pos.y, &pos.z, &rot.x, &rot.y, &rot.z, 
																		     &color.x, &color.y, &color.z, &color.w, &height, &width, &pTextureName, &zIndex);
		if(res == EOF)
			break;

		switch(actorType)
		{
				case ACTORTYPE_SIMPLE:	
#ifdef XBOX
										sprintf(textureAbsolutePath,"Game:\\Content\\Textures\\%s",pTextureName);
#else
										sprintf(textureAbsolutePath, "Content\\Textures\\%s", pTextureName);
#endif
										pTex = ResourceManager::GetInstance()->Load<Texture>(textureAbsolutePath);

										pActorToAdd = new SimpleActor(eAssetType, pos, rot, scale, color, height, width, pTex->GetTexture(), zIndex);						
										break;

				case ACTORTYPE_ANIMATED:	
#ifdef XBOX
										sprintf(textureAbsolutePath,"Game:\\Content\\Textures\\%s",pTextureName);
#else
										sprintf(textureAbsolutePath, "Content\\Textures\\%s", pTextureName);
#endif
										pTex = ResourceManager::GetInstance()->Load<Texture>(textureAbsolutePath);
										fscanf(fp," %d ",&scroll);

										pActorToAdd = new AnimatedActor(eAssetType, pos, rot, scale, color, height, width, pTex->GetTexture(), zIndex, scroll);	
										break;

				case ACTORTYPE_PHYSICS:
										XMVECTOR velocity, acceleration;
										float mass, damping;

										fscanf(fp,"%f %f %f  %f %f %f  %f  %f",&velocity.x, &velocity.y, &velocity.z, &acceleration.x, 
																				&acceleration.y, &acceleration.z, &mass, &damping);
#ifdef XBOX
										sprintf(textureAbsolutePath,"Game:\\Content\\Textures\\%s",pTextureName);
#else
										sprintf(textureAbsolutePath,"Content\\Textures\\%s",pTextureName);
#endif
										pTex = ResourceManager::GetInstance()->Load<Texture>(textureAbsolutePath);

										pActorToAdd = new PhysicsActor(eAssetType, pos, rot, scale, color, height, width, pTex->GetTexture(), zIndex, velocity, acceleration, mass, damping);							
										break;

				default:				break;
		}
		World::GetInstance()->AddActor(pActorToAdd);
	}
	fclose(fp);
}

