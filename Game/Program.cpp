// Program.cpp : Defines the entry point for the application.
#include "Program.h"

BOOL				InitInstance(HINSTANCE, int);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);	

	// we are going to just create a new game every load right now
	NewGameLoader newGameLoader;

	MainWindow* mainWindow = new MainWindow(newGameLoader.GetGameData(),hInstance);
	mainWindow->Show();

	return 0;
}

