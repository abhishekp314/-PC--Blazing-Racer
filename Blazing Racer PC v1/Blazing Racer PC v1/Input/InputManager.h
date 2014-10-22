#pragma once

#ifndef __INPUTMGR__
#define __INPUTMGR__

#include<iostream>

class InputManager
{
	static InputManager			*ms_pInputManager;
	XINPUT_STATE				m_XInputState;
	char						m_Input;

	InputManager();
public:

	~InputManager(void);

	static InputManager*		GetInstance();
	void						Init();
	void						Update();
	void						Destroy();
	bool						GetKeyState(int _key);
	float						GetRightTriggerValue();
	float						GetLeftTriggerValue();
	XMFLOAT2					GetLeftThumbStickValue();
	XMFLOAT2					GetRightThumbStickValue();
	char						GetInput()					{ return m_Input; }
};


#endif