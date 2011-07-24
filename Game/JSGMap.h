#pragma once

#include "stdafx.h"
#include "MapHex.h"
#include <vector>

class JSGMap{

	std::vector<MapHex> _map;

	int Width;
	int Height;
public:	
	JSGMap(int width,int height);
	~JSGMap();
	
	void SetTerrain(int x,int y,HexTerrain* pHexTerrain);
	HexTerrain* GetTerrain(int x,int y);
	int GetWidth();
	int GetHeight();
};
