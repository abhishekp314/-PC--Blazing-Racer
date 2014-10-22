#include "stdafx.h"
#include "Camera.h"

namespace Graphics
{
	Camera::Camera(void)
	{
		m_mProjMat = XMMatrixIdentity();
		m_mViewMat = XMMatrixIdentity();
		m_vLookAt.x = 0.0f;
		m_vLookAt.y = 0.0f;
		m_vLookAt.z = -1.0f;
		m_vLookAt.w = 0.0f;

		m_vEye.x = 0.0f;
		m_vEye.y = 0.0f;
		m_vEye.z = 0.0f;
		m_vEye.w = 0.0f;

		m_Target = XMFLOAT3(0,0,0);
	}

	Camera::~Camera(void)
	{
	}


	bool Camera::InitCamera()
	{
	
		//m_mProjMat = XMMatrixPerspectiveFovLH( XM_PIDIV4, (float)16/9, 1.0f, 200.0f );
		return true;
	}

	void Camera::SetTarget(XMFLOAT3 _target,float _zoomFactor)
	{
		_zoomFactor = 1;
		m_mProjMat = XMMatrixOrthographicLH(1280*_zoomFactor,720*_zoomFactor,-1,10);
		m_Target  = _target;

		m_vLookAt = Float3ToVec(_target);
		m_vLookAt.w = 0;
		m_vEye.x  =  m_Target.x;
		m_vEye.y  =  m_Target.y;
		m_vEye.z  =  -1;
	}
	void Camera::Update()
	{
		XMVECTOR vUp       = { 0.0f, 1.0f, 0.0f, 0.0f };

		m_mViewMat = XMMatrixLookAtLH( m_vEye, m_vLookAt, vUp );

		return;
	}
	void Camera::Destroy()
	{

	}

}


