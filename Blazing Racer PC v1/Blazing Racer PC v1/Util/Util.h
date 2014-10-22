#pragma once
#ifndef __UTIL_
#define __UTIL_

namespace Util
{
	struct QUAD
	{
		XMFLOAT3 a;
		XMFLOAT3 b;
		XMFLOAT3 c;
		XMFLOAT3 d;
		float	 width;
		float	 height;
	};

	struct COLORVERTEX
	{
		float POSITION[3];
		DWORD Color;
	};

	struct TEXVERTEX
	{
		float POSITION[3];
		float TEXCOORD[2];
	};

	class Util
	{
	public:
		Util(void);
		~Util(void);
	};

	XMFLOAT3 VecToFloat3(XMVECTOR _vec);

	XMVECTOR Float3ToVec(XMFLOAT3 _value);

	struct TimeInfo
	{    
		LARGE_INTEGER qwTime;    
		LARGE_INTEGER qwAppTime;   

		float fAppTime;    
		float fElapsedTime;    

		float fSecsPerTick;    
	};

	struct WaveData
	{
		int	  waveIndex;
		short pitchLevel;
		short volumeLevel;
	};
}

#endif

