#pragma once

#include "stdafx.h"
#include <d3d9.h> 
#include <d3dx9.h> 
#include "JSGMap.h"

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

class JSGMapRenderer{
	LPDIRECT3D9       g_pD3D;
	LPDIRECT3DDEVICE9 g_pd3dDevice;
	ID3DXSprite* lp_Sprite;
	
	LPDIRECT3DTEXTURE9 texture;

	HWND _hWnd;

	int Left;
	int Top;	

	void init();

public:

	JSGMapRenderer(HWND hWnd);
	~JSGMapRenderer();

	void AdjustViewPort(int left,int top);

	HRESULT Draw(JSGMap* map,RECT windowRect);	
};