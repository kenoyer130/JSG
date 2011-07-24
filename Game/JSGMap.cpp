#include "JSGMap.h"

using namespace std;

JSGMap::JSGMap(int width,int height){
	Width = width;
	Height = height;

	for(int x = 0;x<width;x++){
		for(int y = 0;y<height;y++){			
			MapHex mapHex;
			_map.push_back(mapHex);
		}
	}
}

JSGMap::~JSGMap(){
	_map.~vector();
}

void JSGMap::SetTerrain(int x,int y,HexTerrain* pHexTerrain){
	MapHex mapHex =_map[x+y];
	mapHex.pHexTerrain=pHexTerrain;
}

HexTerrain* JSGMap::GetTerrain(int x,int y){
	return _map[x+y].pHexTerrain;
}

int JSGMap::GetWidth(){
	return Width;
}

int JSGMap::GetHeight(){
	return Height;
}