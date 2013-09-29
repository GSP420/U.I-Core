#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

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

	bool					WHeld();
	bool					AHeld();
	bool					SHeld();
	bool					DHeld();
	bool					SpaceBarHeld();



private:
	LPDIRECTINPUT8			m_pDIObject;
	LPDIRECTINPUTDEVICE8	m_pDIKeyboardDevice;

	char					KeyBuffer[256];
	bool					KeyWasDown[5];
};