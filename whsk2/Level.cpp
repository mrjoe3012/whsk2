#include "Level.h"
#include "Input.h"
#include "EngineManager.h"
#include "LuaLevel.h"

using Engine::Internal::EngineManager;
using Engine::Level;

Level* Level::loadedLevel = nullptr;

void Level::UpdateCall()
{
	if (loadedLevel)
		loadedLevel->Update();
}

void Level::QuitCall(int exitCode)
{
	if (loadedLevel)
		loadedLevel->OnQuit(exitCode);
}

void Level::ResetEnvironment()
{
	Input::Update(0, 0, 0);
	EngineManager::cameraPos = Vector2D(0, 0);
}

void Level::LoadLevel(std::string file)
{
	if (loadedLevel)
	{
		loadedLevel->OnUnload();
		delete loadedLevel;
	}

	LuaLevel* level = new LuaLevel(file);

	loadedLevel = (Level*)(level);
	ResetEnvironment();
	loadedLevel->OnLoad();
}