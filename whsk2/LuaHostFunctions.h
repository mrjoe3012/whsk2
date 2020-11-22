#pragma once
#include "LuaManager.h"
#include "Engine.h"
USING_ENGINE

class LuaHostFunctions
{
public:
	static void RegisterAll(lua_State* L);

	static int l_ActorNew(lua_State* L);
	static int l_ActorDestroy(lua_State* L);
	static int l_ActorUpdate(lua_State* L);
	static int l_ActorAddComponent(lua_State* L);
	static int l_ActorGetComponent(lua_State* L);
	static int l_ActorRemoveComponent(lua_State* L);

	static int l_GetDeltaTime(lua_State* L);

	static int l_GetKeyCodes(lua_State* L);
	static int l_KeyHeld(lua_State* L);
	static int l_KeyReleased(lua_State* L);
	static int l_AnyKey(lua_State* L);
	static int l_AnyKeyReleased(lua_State* L);

	static int l_ComponentUpdate(lua_State* L);
	static int l_RendererUpdate(lua_State* L);
	static int l_RectRendererUpdate(lua_State* L);
	static int l_EllipseRendererUpdate(lua_State* L);
	static int l_SpriteRendererUpdate(lua_State* L);
	static int l_SpriteRendererSetSprite(lua_State* L);
	static int l_SpriteRendererGetSprite(lua_State* L);

	static Vector2D GetVector2D(lua_State* L);
	static Colour GetColour(lua_State* L);

};