#include "stdafx.h"
#include "Input/InputManager.h"

InputManager* InputManager::ms_pInputManager=nullptr;
InputManager::InputManager(void)
{
	m_Input = 0;
}

InputManager::~InputManager(void)
{
}


void InputManager::Init()
{
	ZeroMemory(&m_XInputState,sizeof(XINPUT_STATE));
	XInputGetState(0,&m_XInputState);
}

bool InputManager::GetKeyState(int _key)
{
	XInputGetState(0,&m_XInputState);

	if((m_XInputState.Gamepad.wButtons & _key))
		return true;

	return false;
}

float InputManager::GetRightTriggerValue()
{
	return m_XInputState.Gamepad.bRightTrigger;
}

float InputManager::GetLeftTriggerValue()
{
	return m_XInputState.Gamepad.bLeftTrigger;
}

XMFLOAT2 InputManager::GetLeftThumbStickValue()
{
	return XMFLOAT2(m_XInputState.Gamepad.sThumbLX, m_XInputState.Gamepad.sThumbLY);
}

XMFLOAT2 InputManager::GetRightThumbStickValue()
{
	return XMFLOAT2(m_XInputState.Gamepad.sThumbRX, m_XInputState.Gamepad.sThumbRY);
}

InputManager* InputManager::GetInstance()
{
	if(ms_pInputManager==nullptr)
		ms_pInputManager=new InputManager;
	return ms_pInputManager;
}


void InputManager::Update()
{
	XMFLOAT2 leftThumbXY = GetLeftThumbStickValue();

	if ((GetRightTriggerValue() > 30) || (GetAsyncKeyState('W') & 0x8000))
	{
		m_Input=m_Input | 1;
	}
	else
	{
		m_Input=m_Input & ~1;
	}


	if ((GetLeftTriggerValue() >  30) || (GetAsyncKeyState(VK_SPACE)))
	{
		m_Input=m_Input | 2;
	}
	else
	{
		m_Input=m_Input & ~2;
	}


	if ((leftThumbXY.x < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) || (GetAsyncKeyState('A') & 0x8000))
	{
		m_Input=m_Input | 4;
	}
	else
	{
		m_Input=m_Input & ~4;
	}


	if ((leftThumbXY.x > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) || (GetAsyncKeyState('D') & 0x8000))
	{
		m_Input=m_Input | 8;
	}
	else
	{
		m_Input=m_Input & ~8;
	}

	if ((GetKeyState(XINPUT_GAMEPAD_START)) || (GetAsyncKeyState(VK_ESCAPE)))
	{
		m_Input=m_Input | 16;
	}
	else
	{
		m_Input=m_Input & ~16;
	}

	if ((GetKeyState(XINPUT_GAMEPAD_LEFT_SHOULDER)) || (GetAsyncKeyState(VK_LSHIFT)))
	{
		m_Input=m_Input | 32;
	}
	else
	{
		m_Input=m_Input & ~32;
	}

	if ((GetKeyState(XINPUT_GAMEPAD_B)) || (GetAsyncKeyState(VK_UP)))
	{
		m_Input=m_Input | 64;
	}
	else
	{
		m_Input=m_Input & ~64;
	}

	if ((GetKeyState(XINPUT_GAMEPAD_X)) || (GetAsyncKeyState(VK_DOWN)))
	{
		m_Input=m_Input | 128;
	}
	else
	{
		m_Input=m_Input & ~128;
	}
}


void InputManager::Destroy()
{

}