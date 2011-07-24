#include "JSGMapRenderer.h"

JSGMapRenderer::JSGMapRenderer(HWND hWnd){
	Left = 0 ;
	Top = 0;

	HRESULT hr;

	_hWnd = hWnd;
	
	init();

	if(FAILED(hr = D3DXCreateSprite(g_pd3dDevice, &lp_Sprite ))){		
		return;
	}

	if(FAILED(hr = D3DXCreateTextureFromFile(g_pd3dDevice,   //Direct3D Device
		L"C:\\projects\\JSG3\\Data\\sprites\\ocean.png",       //File Name
		&texture))){		
		return;
	}
}

JSGMapRenderer::~JSGMapRenderer(){
	if( lp_Sprite != NULL ) 
	{
		lp_Sprite->Release();
		lp_Sprite=NULL;		
	}
}

void JSGMapRenderer::AdjustViewPort(int top,int left){

	Left+=left;
	Top+=top;	
}

HRESULT JSGMapRenderer::Draw(JSGMap* map,RECT windowRect){

	HRESULT hr;
	hr = S_OK;
	
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,  0x00000000, 1.0f, 0 );

	D3DVIEWPORT9 viewPort = { 0,0 , windowRect.right-200, windowRect.bottom-100, 0.0f, 1.0f };

	g_pd3dDevice->SetViewport(&viewPort);

	float z= 0;

	bool indent = false;

	g_pd3dDevice->BeginScene();
	{
		for(int y=0;y<map->GetHeight();y++){

			float tY = y * 16;		

			float tIndent = 0;

			for(int x=0;x<map->GetWidth();x++){
				float tX = x * 64;	

				if(tX==0){
					if(!indent){
						indent = true;
					}else{
						tIndent = 32;
						indent = false;
					}
				}

				D3DXVECTOR3 dCoords((tX+tIndent)-Left,tY-Top,z);

				lp_Sprite->Begin(D3DXSPRITE_ALPHABLEND);
				lp_Sprite->Draw(texture, NULL, NULL, &dCoords, 0xFFFFFFFF);
				lp_Sprite->End();
			}
		}
	}

	g_pd3dDevice->EndScene();

	g_pd3dDevice->Present(NULL, NULL, NULL, NULL );

	return hr;
}

void JSGMapRenderer :: init(){
	g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	if( g_pD3D == NULL )
	{
		// TO DO: Respond to failure of Direct3DCreate8
		return;
	}

	D3DDISPLAYMODE d3ddm;

	if( FAILED( g_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
	{
		// TO DO: Respond to failure of GetAdapterDisplayMode
		return;
	}

	HRESULT hr;

	if( FAILED( hr = g_pD3D->CheckDeviceFormat( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
		d3ddm.Format, D3DUSAGE_DEPTHSTENCIL,
		D3DRTYPE_SURFACE, D3DFMT_D16 ) ) )
	{
		if( hr == D3DERR_NOTAVAILABLE )
			// POTENTIAL PROBLEM: We need at least a 16-bit z-buffer!
			return;
	}

	//
	// Do we support hardware vertex processing? if so, use it. 
	// If not, downgrade to software.
	//

	D3DCAPS9 d3dCaps;

	if( FAILED( g_pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL, &d3dCaps ) ) )
	{
		// TO DO: Respond to failure of GetDeviceCaps
		return;
	}

	DWORD dwBehaviorFlags = 0;

	if( d3dCaps.VertexProcessingCaps != 0 )
		dwBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		dwBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	//
	// Everything checks out - create a simple, windowed device.
	//

	D3DPRESENT_PARAMETERS d3dpp;
	memset(&d3dpp, 0, sizeof(d3dpp));

	d3dpp.BackBufferFormat       = d3ddm.Format;
	d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed               = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;

	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hWnd,
		dwBehaviorFlags, &d3dpp, &g_pd3dDevice ) ) )
	{
		// TO DO: Respond to failure of CreateDevice
		return;
	}
}

