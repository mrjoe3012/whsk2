#include "LuaManager.h"
#include "LuaHostFunctions.h"

using Engine::EngineConfig;
using Engine::Colour;
using Engine::LuaManager;

lua_State* LuaManager::L = nullptr;

std::vector<std::string> LuaManager::coreLibs = 
{
	"ComponentType.lua",
	"KeyCode.lua",
	"KeyState.lua",
	"Input.lua",
	"Vector2.lua",
	"Transform.lua",
	"Colour.lua",
	"Actor.lua",
	"Level.lua",
	"Component.lua",
	"Renderer.lua",
	"RectRenderer.lua",
	"EllipseRenderer.lua",
	"SpriteRenderer.lua"
};

lua_State* LuaManager::GetState()
{
	return L;
}

void LuaManager::DoFile(std::string file)
{
	HandleError(L, luaL_dofile(L, file.c_str()));
}

void LuaManager::Init()
{
	L = luaL_newstate();
	luaL_openlibs(L);
	LoadCoreLibs();
}

void LuaManager::LoadCoreLibs()
{
	std::string prefix = "lua/corelibs/";

	LuaHostFunctions::RegisterAll(L);

	for (auto libname : coreLibs)
	{
		HandleError(L, luaL_dofile(L, (prefix + libname).c_str()));
	}
}

void LuaManager::Release()
{
	if (L)
		lua_close(L);
}

void LuaManager::Reset(lua_State* L)
{
	lua_settop(L, 0);
	LoadCoreLibs();
}

EngineConfig LuaManager::GetConfig(const char* filename)
{
	EngineConfig config;

	HandleError(L, luaL_dofile(L, filename));

	std::string lastField = "";

	try
	{

		lastField = "windowWidth";

		config.windowWidth = (int)GetGlobalNumber(L, "windowWidth");

		lastField = "windowHeight";

		config.windowHeight = (int)GetGlobalNumber(L, "windowHeight");

		lastField = "firstLevel";
		
		config.firstLevel = GetGlobalString(L, "firstLevel");

		lastField = "debugMode";

		config.debug = GetGlobalBoolean(L, "debugMode");

		lastField = "physicsLayerCount";

		config.physicsLayerCount = (int)GetGlobalNumber(L, "physicsLayerCount");

		lastField = "windowTitle";

		config.windowTitle = GetGlobalString(L, "windowTitle");

		lastField = "backgroundColour";

		lua_getglobal(L, "backgroundColour");

		config.backgroundColour.r = (float)GetFieldNumber(L, "r");
		config.backgroundColour.g = (float)GetFieldNumber(L, "g");
		config.backgroundColour.b = (float)GetFieldNumber(L, "b");
		config.backgroundColour.a = 1.0f;

		lua_pop(L, 1);

	}
	catch (std::runtime_error e)
	{
		throw std::runtime_error("Error when attempting to read " + lastField + " from config.");
	}

	Reset(L);

	return config;

}

void LuaManager::HandleError(lua_State* L, int error)
{
	if (error != LUA_OK)
	{
		std::string message = lua_tostring(L, -1);
		throw std::runtime_error(std::string("LUA returned an error: ") + message);
	}
}

double LuaManager::GetGlobalNumber(lua_State* L, const char* name)
{

	lua_getglobal(L, name);

	if (!lua_isnumber(L, -1))
	{
		throw std::runtime_error("Unexpected type.");
	}

	double value = lua_tonumber(L, -1);
	lua_pop(L, 1);
	return value;
}

std::string LuaManager::GetGlobalString(lua_State* L, const char* name)
{

	lua_getglobal(L, name);

	if (!lua_isstring(L, -1))
	{
		throw std::runtime_error("Unexpected type.");
	}

	std::string value = lua_tostring(L, -1);
	lua_pop(L, 1);
	return value;
}

bool LuaManager::GetGlobalBoolean(lua_State* L, const char* name)
{
	lua_getglobal(L, name);

	if (!lua_isboolean(L, -1))
	{
		throw std::runtime_error("Unexpected type.");
	}

	bool value = (bool)lua_toboolean(L, -1);
	lua_pop(L, 1);
	return value;
}

std::string LuaManager::GetFieldString(lua_State* L, const char* name)
{
	std::string result;
	lua_pushstring(L, name);
	lua_gettable(L, -2);
	if (!lua_isstring(L, -1))
		throw std::runtime_error("Unexpected type.");
	result = lua_tostring(L, -1);
	lua_pop(L, 1);
	return result;
}

double LuaManager::GetFieldNumber(lua_State* L, const char* name)
{
	double result;
	lua_pushstring(L, name);
	lua_gettable(L, -2);
	if (!lua_isnumber(L, -1))
		throw std::runtime_error("Unexpected type.");
	result = lua_tonumber(L, -1);
	lua_pop(L, 1);
	return result;
}

bool LuaManager::GetFieldBoolean(lua_State* L, const char* name)
{
	bool result;
	lua_pushstring(L, name);
	lua_gettable(L, -2);
	if (!lua_isboolean(L, -1))
		throw std::runtime_error("Unexpected type.");
	result = lua_toboolean(L, -1);
	lua_pop(L, 1);
	return result;
}