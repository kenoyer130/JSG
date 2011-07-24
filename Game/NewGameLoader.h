#pragma once

#include "GameData.h"

class NewGameLoader{
public:
	NewGameLoader();
	~NewGameLoader();

	GameData* GetGameData();
};