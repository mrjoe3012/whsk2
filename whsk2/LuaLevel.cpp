#include "LuaLevel.h"

using Engine::LuaLevel;

LuaLevel* LuaLevel::instance = nullptr;

LuaLevel::LuaLevel(std::string file)
	:
	filename(file)
{

}

LuaLevel::~LuaLevel()
{
}

void LuaLevel::OnLoad()
{
	instance = this;
	LuaManager::DoFile(filename);

	lua_State* L = LuaManager::GetState();

	lua_getglobal(L, "Level");

	lua_getfield(L, -1, "OnLoad");

	LuaManager::HandleError(L, lua_pcall(L, 0, 0, 0));

	lua_pop(L, 1);
}

void LuaLevel::OnUnload()
{

	lua_State* L = LuaManager::GetState();

	lua_getglobal(L, "Level");

	lua_getfield(L, -1, "_unloadCall");

	LuaManager::HandleError(L, lua_pcall(L, 0, 0, 0));

	lua_pop(L, 1);

	for (Actor* a : this->actors)
	{
		delete a;
	}

	instance = nullptr;
}

void LuaLevel::Update()
{
	lua_State* L = LuaManager::GetState();

	lua_getglobal(L, "Level");

	lua_getfield(L, -1, "_updateCall");

	LuaManager::HandleError(L, lua_pcall(L, 0, 0, 0));

	lua_pop(L, 1);
}

void LuaLevel::OnQuit(int code)
{

}