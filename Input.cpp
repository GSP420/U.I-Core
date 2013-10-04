#include "Input.h"
#include <direct.h>

//Macro needed to reply whether or not a key being checked was pressed
#define KEYDOWN(name, key) (name[key] & 0x80)


Input::Input(void)
{
	m_pDIObject = NULL;
	m_pDIKeyboardDevice = NULL;
	m_pDIMouseDevice = NULL;
	
	//Clears the buffer before use
	ZeroMemory(&KeyBuffer, 256);

	if(!InitDirectInput()) MessageBox (NULL, "InitDirectInput Failed", "ERROR", MB_OK);
	else if(!InitKeyboard()) MessageBox (NULL, "InitKeyboard Failed", "ERROR", MB_OK);
	else if(!InitMouse()) MessageBox (NULL, "InitMouse Failed", "Error", MB_OK);
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

if(FAILED(m_pDIKeyboardDevice->SetCooperativeLevel(NULL,DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
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

bool Input::InitMouse(void)
{
//device capabilities
DIDEVCAPS MouseCapabilities; 

if(FAILED(m_pDIObject->CreateDevice(GUID_SysMouse,&m_pDIMouseDevice,NULL)))
 {
 MessageBox(NULL,"CreateDevice() failed!","InitMouse()",MB_OK);
 return false;
 }

if(FAILED(m_pDIMouseDevice->SetDataFormat(&c_dfDIMouse2)))
 {
 MessageBox(NULL,"SetDataFormat() failed!","InitMouse()",MB_OK);
 return false;
 }

if(FAILED(m_pDIMouseDevice->SetCooperativeLevel(NULL,DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
 {
 MessageBox(NULL,"SetCooperativeLevel() failed!","InitMouse()",MB_OK);
 return false;
 }

if(FAILED(m_pDIMouseDevice->Acquire()))
 {
 MessageBox(NULL,"Acquire() failed!","InitMouse()",MB_OK);
 return false;
 }

MouseCapabilities.dwSize = sizeof(MouseCapabilities);
m_pDIMouseDevice->GetCapabilities(&MouseCapabilities);

if(!(MouseCapabilities.dwFlags & DIDC_ATTACHED))
 {
 MessageBox(NULL,"Mouse is currently not attached!","InitMouse()",MB_OK);
 return false;
 }

m_dwAxes = MouseCapabilities.dwAxes;
m_dwButtons = MouseCapabilities.dwButtons;

SetCursor("arrow.bmp",0,0,0xffffffff);
SetAttributes(false,1.0f);

return true;
}//InitMouse

bool Input::Update(void)
{
if(FAILED(m_pDIKeyboardDevice->GetDeviceState(sizeof(KeyBuffer),(LPVOID)&KeyBuffer)))
 {
 MessageBox(NULL,"GetDeviceState() failed!","Update()",MB_OK);
 return false;
 }

if(DIERR_INPUTLOST == m_pDIMouseDevice->GetDeviceState(sizeof(m_MouseState),(LPVOID)&m_MouseState))
{
 m_pDIMouseDevice->Acquire();
}

return true;
}//Update

#pragma region KeyInput

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
#pragma endregion KeyInput

#pragma region KeyHeldDown

bool Input::WHeld()
{
	if (KEYDOWN(KeyBuffer, DIK_W))
	{
		return true; 
	}
	return false;
}

bool Input::AHeld()
{
	if (KEYDOWN(KeyBuffer, DIK_A))
	{
		return true;		
	}
	return false;
}

bool Input::SHeld()
{
	if (KEYDOWN(KeyBuffer, DIK_S))
	{
		return true;
	}
	return false;
}

bool Input::DHeld()
{
	if (KEYDOWN(KeyBuffer, DIK_D))
	{
		return true;
	}
	return false;
}

bool Input::SpaceBarHeld()
{
	if (KEYDOWN(KeyBuffer, DIK_SPACE))
	{
		return true;
	}
	return false;
}
#pragma endregion KeyHeldDown

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

 if(m_pDIMouseDevice != NULL)
 {
 m_pDIMouseDevice->Unacquire();
 m_pDIMouseDevice->Release();
 m_pDIMouseDevice = NULL;
 }
 }
}//~Input
