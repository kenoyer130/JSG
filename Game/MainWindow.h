#pragma once

#include "stdafx.h"
#include "GameData.h"
#include "JSGMapRenderer.h"

class MainWindow{
private:
	JSGMapRenderer* _JSGMapRenderer;
	
	void RenderMap(HWND hWnd);	
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:

	GameData* _GameData;

	MainWindow(GameData* gameData,HINSTANCE hinstance);
	~MainWindow();

	void Show();		
};