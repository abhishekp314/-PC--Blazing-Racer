#pragma once
#ifndef __CAMERA_
#define __CAMERA_

namespace Graphics
{
	class Camera
	{
	private:
	XMFLOAT3 m_Target;
	XMFLOAT3 m_vOffset;

	XMVECTOR m_vLookAt,m_vEye;

	XMMATRIX m_mViewMat;
	XMMATRIX m_mProjMat;

	
	public:
		Camera(void);
		~Camera(void);

		bool		InitCamera();
		void		SetTarget(XMFLOAT3 target, float _zoomTarget);//Change this to a pointer of target object.
		void		Update();
		void		Destroy();

		XMMATRIX	GetViewMat(){return m_mViewMat;}
		XMMATRIX	GetProjMat(){return m_mProjMat;}
		XMFLOAT3	GetCameraPosition(){ return m_Target; }
	};

}


#endif

