#include "Input.h"
#include <direct.h>

//Macro needed to reply whether or not a key being checked was pressed
#define KEYDOWN(name, key) (name[key] & 0x80)


Input::Input(void)
{
	m_pDIObject = NULL;
	m_pDIKeyboardDevice = NULL;

	

	//Clears the buffer before use
	ZeroMemory(&KeyBuffer, 256);

	if(!InitDirectInput()) MessageBox (NULL, "InitDirectInput Failed", "ERROR", MB_OK);
	else if(!InitKeyboard()) MessageBox (NULL, "InitKeyboard Failed", "ERROR", MB_OK);
}//Input


bool Input::InitDirectInput(void)
{
if(FAILED(DirectInput8Create(GetModuleHandle(NULL),DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&m_pDIObject,NULL)))
 {
 MessageBox(NULL,"DirectInput8Create() failed!","InitDirectInput()",MB_OK);
 return false;
 }

return true;
}//InitDirectInput

bool Input::InitKeyboard(void)
{
if(FAILED(m_pDIObject->CreateDevice(GUID_SysKeyboard,&m_pDIKeyboardDevice,NULL)))
 {
 MessageBox(NULL,"CreateDevice() failed!","InitKeyboard()",MB_OK);
 return false;
 }

if(FAILED(m_pDIKeyboardDevice->SetDataFormat(&c_dfDIKeyboard)))
 {
 MessageBox(NULL,"SetDataFormat() failed!","InitKeyboard()",MB_OK);
 return false;
 }

if(FAILED(m_pDIKeyboardDevice->SetCooperativeLevel(g_App.GetWindowHandle(),DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
 {
 MessageBox(NULL,"SetCooperativeLevel() failed!","InitKeyboard()",MB_OK);
 return false;
 }

if(FAILED(m_pDIKeyboardDevice->Acquire()))
 {
 MessageBox(NULL,"Acquire() failed!","InitKeyboard()",MB_OK);
 return false;
 }

return true;
}//InitKeyboard

bool Input::Update(void)
{
if(FAILED(m_pDIKeyboardDevice->GetDeviceState(sizeof(KeyBuffer),(LPVOID)&KeyBuffer)))
 {
 MessageBox(NULL,"GetDeviceState() failed!","Update()",MB_OK);
 return false;
 }

return true;
}//Update

bool KeyWasDown[5];

bool Input::WPressed()
{
	if (KEYDOWN(KeyBuffer, DIK_W))
	{
		KeyWasDown[0] = true;
		return false;
	}

	if (!KEYDOWN(KeyBuffer, DIK_W) && KeyWasDown[0])
	{
		KeyWasDown[0] = false;
		return true;
	}

	return false;
}

bool Input::APressed()
{
	if (KEYDOWN(KeyBuffer, DIK_A))
	{
		KeyWasDown[1] = true;
		return false;
	}

	if (!KEYDOWN(KeyBuffer, DIK_A) && KeyWasDown[1])
	{
		KeyWasDown[1] = false;
		return true;
	}

	return false;
}

bool Input::SPressed()
{
	if (KEYDOWN(KeyBuffer, DIK_S))
	{
		KeyWasDown[2] = true;
		return false;
	}

	if (!KEYDOWN(KeyBuffer, DIK_S) && KeyWasDown[2])
	{
		KeyWasDown[2] = false;
		return true;
	}

	return false;
}

bool Input::DPressed()
{
	if (KEYDOWN(KeyBuffer, DIK_D))
	{
		KeyWasDown[3] = true;
		return false;
	}

	if (!KEYDOWN(KeyBuffer, DIK_D) && KeyWasDown[3])
	{
		KeyWasDown[3] = false;
		return true;
	}

	return false;
}

bool Input::SpaceBar()
{
	if (KEYDOWN(KeyBuffer, DIK_SPACE))
	{
		KeyWasDown[4] = true;
		return false;
	}

	if (!KEYDOWN(KeyBuffer, DIK_SPACE) && KeyWasDown[4])
	{
		KeyWasDown[4] = false;
		return true;
	}

	return false;
}

Input::~Input(void)
{
if(m_pDIKeyboardDevice != NULL)
 {
 m_pDIKeyboardDevice->Unacquire();
 m_pDIKeyboardDevice->Release();
 m_pDIKeyboardDevice = NULL;
 }

if(m_pDIObject != NULL)
 {
 m_pDIObject->Release();
 m_pDIObject = NULL;
 }
}//~Input
