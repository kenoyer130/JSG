#include "GameData.h"

GameData::GameData(){}

GameData::~GameData(){
	_JSGMap->~JSGMap();
}
