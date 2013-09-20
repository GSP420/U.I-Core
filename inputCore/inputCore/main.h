#ifndef main_h
#define main_h

//includes
#include<windows.h>
#include<commctrl.h>
#include<d3d9.h>
#include<d3dx9.h>
#include<dinput.h>
#include<fstream>

using namespace std;

#include"Application.h"
#include"Input.h"
#include"d3ddefs.h"

//globals
//extern Application			g_App;
extern Input*				g_Input;

//functions
LRESULT CALLBACK			WindowProcedure(HWND,UINT,WPARAM,LPARAM);

#endif