//=============================================================================
// Name: DirectInputClass.h
//	Des: ��װ��DirectInput�������봦�����ͷ�ļ�
// 2025�� 9 �� 30 �� Learning by ĭ���
//=============================================================================
#pragma once
#include "D3DUtil.h"
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

class DInputClass
{
private:
	IDirectInput8* m_pDirectInput;
	IDirectInputDevice8* m_KeyboardDevice;
	char m_keyBuffer[256];
	IDirectInputDevice8* m_MouseDevice;
	DIMOUSESTATE m_MouseState;

public:
	HRESULT Init(HWND hwnd, HINSTANCE hInstance, DWORD keyboardCoopFlags, DWORD mouseCoopFlags);
	void GetInput();
	bool IsKeyDown(int iKey);

	bool IsMouseButtonDown(int button);
	float MouseDX();
	float MouseDY();
	float MouseDZ();

public:
	DInputClass(void);
	~DInputClass(void);
};

