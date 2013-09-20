#include"main.h"
#include "Input.h"

Input::Input(void)
{
	m_pDIObject = NULL;
	m_pDIKeyboardDevice = NULL;

	if(!InitDirectInput()) g_App.SetD3DStatus(false);
	else if(!InitKeyboard()) g_App.SetD3DStatus(false);
}//Input

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

bool Input::InitDirectInput(void)
{
if(FAILED(DirectInput8Create(GetModuleHandle(NULL),DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&m_pDIObject,NULL)))
 {
 MessageBox(g_App.GetWindowHandle(),"DirectInput8Create() failed!","InitDirectInput()",MB_OK);
 return false;
 }

return true;
}//InitDirectInput

bool Input::InitKeyboard(void)
{
if(FAILED(m_pDIObject->CreateDevice(GUID_SysKeyboard,&m_pDIKeyboardDevice,NULL)))
 {
 MessageBox(g_App.GetWindowHandle(),"CreateDevice() failed!","InitKeyboard()",MB_OK);
 return false;
 }

if(FAILED(m_pDIKeyboardDevice->SetDataFormat(&c_dfDIKeyboard)))
 {
 MessageBox(g_App.GetWindowHandle(),"SetDataFormat() failed!","InitKeyboard()",MB_OK);
 return false;
 }

if(FAILED(m_pDIKeyboardDevice->SetCooperativeLevel(g_App.GetWindowHandle(),DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
 {
 MessageBox(g_App.GetWindowHandle(),"SetCooperativeLevel() failed!","InitKeyboard()",MB_OK);
 return false;
 }

if(FAILED(m_pDIKeyboardDevice->Acquire()))
 {
 MessageBox(g_App.GetWindowHandle(),"Acquire() failed!","InitKeyboard()",MB_OK);
 return false;
 }

return true;
}//InitKeyboard

bool Input::Update(void)
{
if(FAILED(m_pDIKeyboardDevice->GetDeviceState(sizeof(KeyBuffer),(LPVOID)&KeyBuffer)))
 {
 MessageBox(g_App.GetWindowHandle(),"GetDeviceState() failed!","Update()",MB_OK);
 return false;
 }

return true;
}//Update

bool Input::CheckInput(int Key)
{
if(KeyBuffer[Key] & 0x80)
 {
 return true;
 }

return false;
}//CheckInput