/*



#include"main.h"

//globals
Application	g_App;
Input*			g_pInput;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPreviousInstance,LPSTR lpcmdline,int nCmdShow)
{
MSG Message;
LPDIRECT3DVERTEXBUFFER9 pTriangleVB = NULL;
LPDIRECT3DVERTEXBUFFER9 pQuadVB = NULL;
VOID* pData;
D3DXMATRIX matRotationY,matTranslation;
float fRotation = 0.0f,fX = 0.0f,fY = 0.0f,fZ = 10.0f;
D3DVERTEX aTriangle[] = {{0.0f,1.0f,0.0f,0xffff0000},{-1.0f,-1.0f,-1.0f,0xff00ff00},{1.0f,-1.0f,-1.0f,0xff0000ff},
						{0.0f,1.0f,0.0f,0xffff0000},{-1.0f,-1.0f,1.0f,0xff0000ff},{-1.0f,-1.0f,-1.0f,0xff00ff00},
						{0.0f,1.0f,0.0f,0xffff0000},{1.0f,-1.0f,1.0f,0xff00ff00},{-1.0f,-1.0f,1.0f,0xff0000ff},
						{0.0f,1.0f,0.0f,0xffff0000},{1.0f,-1.0f,-1.0f,0xff0000ff},{1.0f,-1.0f,1.0f,0xff00ff00}};

D3DVERTEX aQuad[] = {{-1.0f,-1.0f,-1.0f,0xffffff00},
					{1.0f,-1.0f,-1.0f,0xffffff00},
					{-1.0f,-1.0f,1.0f,0xffffff00},
					{1.0f,-1.0f,1.0f,0xffffff00}};

//window loop
while(g_App.GetWindowStatus())
 {
 if(GetMessage(&Message,NULL,0,0))
  {
  if(!IsDialogMessage(g_App.GetWindowHandle(),&Message))
   {
   TranslateMessage(&Message);
   DispatchMessage(&Message);
   }
  }
 }

//switch to D3D loop or quit
if(!g_App.GetD3DStatus())
 return 0;

g_App.GetDevice()->CreateVertexBuffer(sizeof(aTriangle),D3DUSAGE_WRITEONLY,D3DFVF_CUSTOMVERTEX,D3DPOOL_MANAGED,&pTriangleVB,NULL);
g_App.GetDevice()->CreateVertexBuffer(sizeof(aQuad),D3DUSAGE_WRITEONLY,D3DFVF_CUSTOMVERTEX,D3DPOOL_MANAGED,&pQuadVB,NULL);

pTriangleVB->Lock(0,sizeof(pData),(void**)&pData,0);
memcpy(pData,aTriangle,sizeof(aTriangle));
pTriangleVB->Unlock();

pQuadVB->Lock(0,sizeof(pData),(void**)&pData,0);
memcpy(pData,aQuad,sizeof(aQuad));
pQuadVB->Unlock();

g_pInput = new CInput;

//D3D loop
while(g_App.GetD3DStatus())
 {
 if(PeekMessage(&Message,NULL,0,0,PM_REMOVE))
  {
  TranslateMessage(&Message);
  DispatchMessage(&Message);
  }

 if(g_App.CheckDevice())
  {
  g_pInput->Update();
  if(g_pInput->KeyPressed(DIK_RIGHT)) fX += 0.01f;
  if(g_pInput->KeyPressed(DIK_LEFT)) fX -= 0.01f;
  if(g_pInput->KeyPressed(DIK_UP)) fZ += 0.01f;
  if(g_pInput->KeyPressed(DIK_DOWN)) fZ -= 0.01f;
  if(g_pInput->KeyPressed(DIK_PRIOR)) fY += 0.01f;
  if(g_pInput->KeyPressed(DIK_NEXT)) fY -= 0.01f;
  if(g_pInput->KeyPressed(DIK_HOME)) fRotation += 0.001f;
  if(g_pInput->KeyPressed(DIK_END)) fRotation -= 0.001f;

  g_App.GetDevice()->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0,0,0),1.0f,0);
  g_App.GetDevice()->BeginScene();

  D3DXMatrixRotationY(&matRotationY,fRotation);
  D3DXMatrixTranslation(&matTranslation,fX,fY,fZ);
  g_App.GetDevice()->SetTransform(D3DTS_WORLD,&(matRotationY * matTranslation));

  g_App.GetDevice()->SetStreamSource(0,pTriangleVB,0,sizeof(D3DVERTEX));
  g_App.GetDevice()->DrawPrimitive(D3DPT_TRIANGLELIST,0,4);

  g_App.GetDevice()->SetStreamSource(0,pQuadVB,0,sizeof(D3DVERTEX));
  g_App.GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

  g_App.GetDevice()->EndScene();
  g_App.GetDevice()->Present(NULL,NULL,NULL,NULL);
  }
 }

delete g_pInput;

return 0;
}//WinMain




*/