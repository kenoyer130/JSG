#include "NewGameLoader.h"

NewGameLoader::NewGameLoader(){

}

NewGameLoader::~NewGameLoader(){
	
}

GameData* NewGameLoader::GetGameData(){
	GameData* gameData = new GameData();

	gameData->_JSGMap = new JSGMap(40,40);

	return gameData;
}