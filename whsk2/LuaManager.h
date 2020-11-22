#pragma once

#include "EngineConfig.h"
#include <vector>

extern "C"
{
#include "include/lua/lua.h"
#include "include/lua/lauxlib.h"
#include "include/lua/lualib.h"
}

namespace Engine
{

	class LuaManager
	{

	private:
		static lua_State* L;
		static std::vector<std::string> coreLibs;

		static void LoadCoreLibs();

	public:
		static void HandleError(lua_State* L, int error);

		static std::string GetGlobalString(lua_State* L, const char* name);
		static double GetGlobalNumber(lua_State* L, const char* name);
		static bool GetGlobalBoolean(lua_State* L, const char* name);

		static std::string GetFieldString(lua_State* L, const char* name);
		static double GetFieldNumber(lua_State* L, const char* name);
		static bool GetFieldBoolean(lua_State* L, const char* name);

		static void Init();
		static EngineConfig GetConfig(const char* filename);
		static void Release();
		static void Reset(lua_State* L);
		static void DoFile(std::string file);
		static lua_State* GetState();

	};

}