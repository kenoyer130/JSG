#include "MainWindow.h"
#include "JSGMapRenderer.h"
#include "WindowClassManager.h"

BOOL InitApplication(HINSTANCE hinstance);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

MainWindow::MainWindow(GameData* gameData,HINSTANCE hinstance){
	WindowClassManager::CreateMain(hinstance,MainWindow::WndProc);
	_GameData = gameData;
}

MainWindow::~MainWindow(){	
	_GameData->~GameData();
}

void MainWindow::Show(){	

	HWND hwnd =  CreateWindow(L"MainWClass", // window class name
		L"Main Game Window", // window name
		WS_OVERLAPPEDWINDOW, // style
		CW_USEDEFAULT, //x
		0,  // y
		CW_USEDEFAULT, //width
		0,  // height
		NULL, // parent
		NULL, // menu
		NULL, // instance
		this // pass in ourselves for the message pump
		);

	SetWindowLong(hwnd, GWL_USERDATA, (long)this);

	_JSGMapRenderer=new JSGMapRenderer(hwnd);

	ShowWindow(hwnd,SW_MAXIMIZE);
	UpdateWindow(hwnd);

	MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void MainWindow::RenderMap(HWND hWnd){	
	RECT rect;
	GetClientRect(hWnd,&rect);
	_JSGMapRenderer->Draw(_GameData->_JSGMap,rect);
}

LRESULT CALLBACK MainWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	MainWindow* mainWindow = (MainWindow*)GetWindowLong( hWnd, GWL_USERDATA );

	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
		case WM_KEYDOWN:
		switch(wParam){
			case 40:
				mainWindow->_JSGMapRenderer->AdjustViewPort(10,0);
				break;
			case 38:
				mainWindow->_JSGMapRenderer->AdjustViewPort(-10,0);
				break;
			case 37:
				mainWindow->_JSGMapRenderer->AdjustViewPort(0,-10);
				break;
			case 39:
				mainWindow->_JSGMapRenderer->AdjustViewPort(0,10);
				break;			
		}

		mainWindow->RenderMap(hWnd);

		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);		
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		mainWindow->RenderMap(hWnd);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

