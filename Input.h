#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include"main.h"

class Input
{
public:
							Input(void);
							~Input(void);
	bool					InitDirectInput(void);
	bool					InitKeyboard(void);

	bool					Update(void);

	bool					WPressed();
	bool					APressed();
	bool					SPressed();
	bool					DPressed();
	bool					SpaceBar();



private:
	LPDIRECTINPUT8			m_pDIObject;
	LPDIRECTINPUTDEVICE8	m_pDIKeyboardDevice;

	char					KeyBuffer[256];
};