#include "stdafx.h"
#include "Util/Util.h"

namespace Util
{
	Util::Util(void)
	{
	}


	Util::~Util(void)
	{
	}

	XMFLOAT3 VecToFloat3(XMVECTOR _vec)		
	{ 
		XMFLOAT3 _value = XMFLOAT3(0,0,0);
		_value.x = _vec.x;
		_value.y = _vec.y;
		_value.z = _vec.z;
		return _value;
	}

	XMVECTOR Float3ToVec(XMFLOAT3 _value)	
	{ 
		XMVECTOR vec;
		vec.x = _value.x;
		vec.y = _value.y;
		vec.z = _value.z;
		return vec;
	}

	float lerp(float _x, float _y, float _t) 
	{
		return _x*(1-_t)+_y*_t;
	}
}
