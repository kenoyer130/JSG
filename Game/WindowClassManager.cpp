#include "WindowClassManager.h"

BOOL WindowClassManager::CreateMain(HINSTANCE hinstance,WNDPROC messagePump){

	WNDCLASSEX wcx; 
 
    // Fill in the window class structure with parameters 
    // that describe the main window. 
 
    wcx.cbSize = sizeof(wcx);          // size of structure 
    wcx.style = CS_HREDRAW | CS_VREDRAW;                    // redraw if size changes 
    wcx.lpfnWndProc = messagePump;     // points to window procedure 
    wcx.cbClsExtra = 0;                // no extra class memory 
    wcx.cbWndExtra = 0;                // no extra window memory 
    wcx.hInstance = hinstance;         // handle to instance 
    wcx.hIcon = NULL;              // predefined app. icon 
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);                    // predefined arrow 
    wcx.hbrBackground =  (HBRUSH)GetStockObject(WHITE_BRUSH);                  // white background brush 
    wcx.lpszMenuName =  L"MainMenu";    // name of menu resource 
    wcx.lpszClassName = L"MainWClass";  // name of window class 
    wcx.hIconSm = NULL;
 
    // Register the window class. 
 
    return RegisterClassEx(&wcx); 
}