#include "LuaHostFunctions.h"
#include "LuaLevel.h"
#include "Engine.h"
#include <locale>
#include <codecvt>

USING_ENGINE
using Engine::LuaLevel;
using Engine::Level;

enum ComponentType
{
	RECTRENDERER,
	ELLIPSERENDERER,
	SPRITERENDERER,
	TEXTRENDERER,
	PHYSICSOBJECT,
	ANIMATION,
	AUDIOSOURCE
};

void LuaHostFunctions::RegisterAll(lua_State* L)
{
	lua_register(L, "_get_keycodes", LuaHostFunctions::l_GetKeyCodes);

	lua_register(L, "_input_anykey", LuaHostFunctions::l_AnyKey);
	lua_register(L, "_input_anykeyreleased", LuaHostFunctions::l_AnyKeyReleased);
	lua_register(L, "_input_keyheld", LuaHostFunctions::l_KeyHeld);
	lua_register(L, "_input_keyreleased", LuaHostFunctions::l_KeyReleased);

	lua_register(L, "_actor_new", LuaHostFunctions::l_ActorNew);
	lua_register(L, "_actor_destroy", LuaHostFunctions::l_ActorDestroy);
	lua_register(L, "_actor_update", LuaHostFunctions::l_ActorUpdate);
	lua_register(L, "_actor_addcomponent", LuaHostFunctions::l_ActorAddComponent);
	lua_register(L, "_actor_getcomponent", LuaHostFunctions::l_ActorGetComponent);
	lua_register(L, "_actor_removecomponent", LuaHostFunctions::l_ActorRemoveComponent);

	lua_register(L, "_component_update", LuaHostFunctions::l_ComponentUpdate);
	lua_register(L, "_renderer_update", LuaHostFunctions::l_RendererUpdate);
	lua_register(L, "_rectrenderer_update", LuaHostFunctions::l_RectRendererUpdate);
	lua_register(L, "_ellipserenderer_update", LuaHostFunctions::l_EllipseRendererUpdate);
	lua_register(L, "_spriterenderer_update", LuaHostFunctions::l_SpriteRendererUpdate);
	lua_register(L, "_spriterenderer_setsprite", LuaHostFunctions::l_SpriteRendererSetSprite);
	lua_register(L, "_spriterenderer_getsprite", LuaHostFunctions::l_SpriteRendererGetSprite);
}

int LuaHostFunctions::l_AnyKey(lua_State* L)
{
	lua_settop(L, 0);

	bool anykey = Input::GetAnyKey();

	lua_pushboolean(L, anykey);

	return 1;
}

int LuaHostFunctions::l_AnyKeyReleased(lua_State* L)
{
	lua_settop(L, 0);

	bool anykeyreleased = Input::GetAnyKeyReleased();

	lua_pushboolean(L, anykeyreleased);

	return 1;
}

int LuaHostFunctions::l_KeyHeld(lua_State* L)
{
	
	lua_settop(L, 1);

	int key = luaL_checkinteger(L, 1);

	bool held = Input::GetKeyHeld(GetKeyCodeBits(key));

	lua_pushboolean(L, held);

	return 1;
}

int LuaHostFunctions::l_KeyReleased(lua_State* L)
{
	lua_settop(L, 1);

	int key = luaL_checkinteger(L, 1);

	bool held = Input::GetKeyReleased(GetKeyCodeBits(key));

	lua_pushboolean(L, held);

	return 1;
}

int LuaHostFunctions::l_GetKeyCodes(lua_State* L)
{
	lua_settop(L, 0);

	lua_newtable(L);

	lua_pushstring(L, "ArrowLeft");
	lua_pushinteger(L, KEYCODE_ARROWLEFT);
	lua_settable(L, 1);

	lua_pushstring(L, "ArrowUp");
	lua_pushinteger(L, KEYCODE_ARROWUP);
	lua_settable(L, 1);

	lua_pushstring(L, "ArrowRight");
	lua_pushinteger(L, KEYCODE_ARROWRIGHT);
	lua_settable(L, 1);

	lua_pushstring(L, "Arrowdown");
	lua_pushinteger(L, KEYCODE_ARROWDOWN);
	lua_settable(L, 1);

	lua_pushstring(L, "Q");
	lua_pushinteger(L, KEYCODE_Q);
	lua_settable(L, 1);

	lua_pushstring(L, "W");
	lua_pushinteger(L, KEYCODE_W);
	lua_settable(L, 1);

	lua_pushstring(L, "E");
	lua_pushinteger(L, KEYCODE_E);
	lua_settable(L, 1);

	lua_pushstring(L, "R");
	lua_pushinteger(L, KEYCODE_R);
	lua_settable(L, 1);

	lua_pushstring(L, "T");
	lua_pushinteger(L, KEYCODE_T);
	lua_settable(L, 1);

	lua_pushstring(L, "Y");
	lua_pushinteger(L, KEYCODE_Y);
	lua_settable(L, 1);

	lua_pushstring(L, "U");
	lua_pushinteger(L, KEYCODE_U);
	lua_settable(L, 1);

	lua_pushstring(L, "I");
	lua_pushinteger(L, KEYCODE_I);
	lua_settable(L, 1);

	lua_pushstring(L, "O");
	lua_pushinteger(L, KEYCODE_O);
	lua_settable(L, 1);

	lua_pushstring(L, "P");
	lua_pushinteger(L, KEYCODE_P);
	lua_settable(L, 1);

	lua_pushstring(L, "A");
	lua_pushinteger(L, KEYCODE_A);
	lua_settable(L, 1);

	lua_pushstring(L, "S");
	lua_pushinteger(L, KEYCODE_S);
	lua_settable(L, 1);

	lua_pushstring(L, "D");
	lua_pushinteger(L, KEYCODE_D);
	lua_settable(L, 1);

	lua_pushstring(L, "F");
	lua_pushinteger(L, KEYCODE_F);
	lua_settable(L, 1);

	lua_pushstring(L, "G");
	lua_pushinteger(L, KEYCODE_G);
	lua_settable(L, 1);

	lua_pushstring(L, "H");
	lua_pushinteger(L, KEYCODE_H);
	lua_settable(L, 1);

	lua_pushstring(L, "J");
	lua_pushinteger(L, KEYCODE_J);
	lua_settable(L, 1);

	lua_pushstring(L, "K");
	lua_pushinteger(L, KEYCODE_K);
	lua_settable(L, 1);

	lua_pushstring(L, "L");
	lua_pushinteger(L, KEYCODE_L);
	lua_settable(L, 1);

	lua_pushstring(L, "Z");
	lua_pushinteger(L, KEYCODE_Z);
	lua_settable(L, 1);

	lua_pushstring(L, "C");
	lua_pushinteger(L, KEYCODE_C);
	lua_settable(L, 1);

	lua_pushstring(L, "V");
	lua_pushinteger(L, KEYCODE_V);
	lua_settable(L, 1);

	lua_pushstring(L, "B");
	lua_pushinteger(L, KEYCODE_B);
	lua_settable(L, 1);

	lua_pushstring(L, "N");
	lua_pushinteger(L, KEYCODE_N);
	lua_settable(L, 1);

	lua_pushstring(L, "M");
	lua_pushinteger(L, KEYCODE_M);
	lua_settable(L, 1);

	lua_pushstring(L, "LeftShift");
	lua_pushinteger(L, KEYCODE_LEFTSHIFT);
	lua_settable(L, 1);

	lua_pushstring(L, "LeftControl");
	lua_pushinteger(L, KEYCODE_LEFTCONTROL);
	lua_settable(L, 1);

	lua_pushstring(L, "LeftAlt");
	lua_pushinteger(L, KEYCODE_LEFTALT);
	lua_settable(L, 1);

	lua_pushstring(L, "Space");
	lua_pushinteger(L, KEYCODE_SPACEBAR);
	lua_settable(L, 1);

	lua_pushstring(L, "RightAlt");
	lua_pushinteger(L, KEYCODE_RIGHTALT);
	lua_settable(L, 1);

	lua_pushstring(L, "RightControl");
	lua_pushinteger(L, KEYCODE_RIGHTCONTROL);
	lua_settable(L, 1);

	lua_pushstring(L, "Enter");
	lua_pushinteger(L, KEYCODE_ENTER);
	lua_settable(L, 1);

	lua_pushstring(L, "Return");
	lua_pushinteger(L, KEYCODE_RETURN);
	lua_settable(L, 1);

	lua_pushstring(L, "Backspace");
	lua_pushinteger(L, KEYCODE_BACKSPACE);
	lua_settable(L, 1);

	lua_pushstring(L, "Hash");
	lua_pushinteger(L, KEYCODE_HASHTAG);
	lua_settable(L, 1);

	lua_pushstring(L, "N1");
	lua_pushinteger(L, KEYCODE_1);
	lua_settable(L, 1);

	lua_pushstring(L, "N2");
	lua_pushinteger(L, KEYCODE_2);
	lua_settable(L, 1);

	lua_pushstring(L, "N3");
	lua_pushinteger(L, KEYCODE_3);
	lua_settable(L, 1);

	lua_pushstring(L, "N4");
	lua_pushinteger(L, KEYCODE_4);
	lua_settable(L, 1);

	lua_pushstring(L, "N5");
	lua_pushinteger(L, KEYCODE_5);
	lua_settable(L, 1);

	lua_pushstring(L, "N6");
	lua_pushinteger(L, KEYCODE_6);
	lua_settable(L, 1);

	lua_pushstring(L, "N7");
	lua_pushinteger(L, KEYCODE_7);
	lua_settable(L, 1);

	lua_pushstring(L, "N8");
	lua_pushinteger(L, KEYCODE_8);
	lua_settable(L, 1);

	lua_pushstring(L, "N9");
	lua_pushinteger(L, KEYCODE_9);
	lua_settable(L, 1);

	lua_pushstring(L, "N0");
	lua_pushinteger(L, KEYCODE_0);
	lua_settable(L, 1);

	lua_pushstring(L, "Minus");
	lua_pushinteger(L, KEYCODE_MINUS);
	lua_settable(L, 1);

	lua_pushstring(L, "Equals");
	lua_pushinteger(L, KEYCODE_PLUS);
	lua_settable(L, 1);

	lua_pushstring(L, "Dot");
	lua_pushinteger(L, KEYCODE_FULLSTOP);
	lua_settable(L, 1);

	lua_pushstring(L, "Period");
	lua_pushinteger(L, KEYCODE_FULLSTOP);
	lua_settable(L, 1);

	lua_pushstring(L, "Comma");
	lua_pushinteger(L, KEYCODE_COMMA);
	lua_settable(L, 1);

	lua_pushstring(L, "ForwardSlash");
	lua_pushinteger(L, KEYCODE_FORWARDSLASH);
	lua_settable(L, 1);

	lua_pushstring(L, "BackSlash");
	lua_pushinteger(L, KEYCODE_BACKSLASH);
	lua_settable(L, 1);

	lua_pushstring(L, "SemiColon");
	lua_pushinteger(L, KEYCODE_SEMICOLON);
	lua_settable(L, 1);

	lua_pushstring(L, "Apostrophe");
	lua_pushinteger(L, KEYCODE_APOSTROPHE);
	lua_settable(L, 1);

	lua_pushstring(L, "Insert");
	lua_pushinteger(L, KEYCODE_INSERT);
	lua_settable(L, 1);

	lua_pushstring(L, "Home");
	lua_pushinteger(L, KEYCODE_HOME);
	lua_settable(L, 1);

	lua_pushstring(L, "PageUp");
	lua_pushinteger(L, KEYCODE_PAGEUP);
	lua_settable(L, 1);

	lua_pushstring(L, "Delete");
	lua_pushinteger(L, KEYCODE_DELETE);
	lua_settable(L, 1);

	lua_pushstring(L, "End");
	lua_pushinteger(L, KEYCODE_END);
	lua_settable(L, 1);

	lua_pushstring(L, "PageDown");
	lua_pushinteger(L, KEYCODE_PAGEDOWN);
	lua_settable(L, 1);

	lua_pushstring(L, "NumpadForwardSlash");
	lua_pushinteger(L, KEYCODE_NUMPADFORWARDSLASH);
	lua_settable(L, 1);

	lua_pushstring(L, "NumpadAsterisk");
	lua_pushinteger(L, KEYCODE_NUMPADASTERISK);
	lua_settable(L, 1);

	lua_pushstring(L, "NumpadMinus");
	lua_pushinteger(L, KEYCODE_NUMPADMINUS);
	lua_settable(L, 1);

	lua_pushstring(L, "NumpadPlus");
	lua_pushinteger(L, KEYCODE_NUMPADPLUS);
	lua_settable(L, 1);

	lua_pushstring(L, "NumpadEnter");
	lua_pushinteger(L, KEYCODE_NUMPADENTER);
	lua_settable(L, 1);

	lua_pushstring(L, "NumpadReturn");
	lua_pushinteger(L, KEYCODE_NUMPADRETURN);
	lua_settable(L, 1);

	lua_pushstring(L, "NumpadPeriod");
	lua_pushinteger(L, KEYCODE_NUMPADPERIOD);
	lua_settable(L, 1);

	lua_pushstring(L, "NumpadN0");
	lua_pushinteger(L, KEYCODE_NUMPAD0);
	lua_settable(L, 1);

	lua_pushstring(L, "NumpadN1");
	lua_pushinteger(L, KEYCODE_NUMPAD1);
	lua_settable(L, 1);

	lua_pushstring(L, "NumpadN2");
	lua_pushinteger(L, KEYCODE_NUMPAD2);
	lua_settable(L, 1);

	lua_pushstring(L, "NumpadN3");
	lua_pushinteger(L, KEYCODE_NUMPAD3);
	lua_settable(L, 1);

	lua_pushstring(L, "NumpadN4");
	lua_pushinteger(L, KEYCODE_NUMPAD4);
	lua_settable(L, 1);

	lua_pushstring(L, "NumpadN5");
	lua_pushinteger(L, KEYCODE_NUMPAD5);
	lua_settable(L, 1);

	lua_pushstring(L, "NumpadN6");
	lua_pushinteger(L, KEYCODE_NUMPAD6);
	lua_settable(L, 1);

	lua_pushstring(L, "NumpadN7");
	lua_pushinteger(L, KEYCODE_NUMPAD7);
	lua_settable(L, 1);

	lua_pushstring(L, "NumpadN8");
	lua_pushinteger(L, KEYCODE_NUMPAD8);
	lua_settable(L, 1);

	lua_pushstring(L, "NumpadN9");
	lua_pushinteger(L, KEYCODE_NUMPAD9);
	lua_settable(L, 1);

	lua_pushstring(L, "F1");
	lua_pushinteger(L, KEYCODE_F1);
	lua_settable(L, 1);

	lua_pushstring(L, "F2");
	lua_pushinteger(L, KEYCODE_F2);
	lua_settable(L, 1);

	lua_pushstring(L, "F3");
	lua_pushinteger(L, KEYCODE_F3);
	lua_settable(L, 1);

	lua_pushstring(L, "F4");
	lua_pushinteger(L, KEYCODE_F4);
	lua_settable(L, 1);

	lua_pushstring(L, "F5");
	lua_pushinteger(L, KEYCODE_F5);
	lua_settable(L, 1);

	lua_pushstring(L, "F6");
	lua_pushinteger(L, KEYCODE_F6);
	lua_settable(L, 1);

	lua_pushstring(L, "F7");
	lua_pushinteger(L, KEYCODE_F7);
	lua_settable(L, 1);

	lua_pushstring(L, "F8");
	lua_pushinteger(L, KEYCODE_F8);
	lua_settable(L, 1);

	lua_pushstring(L, "F9");
	lua_pushinteger(L, KEYCODE_F9);
	lua_settable(L, 1);

	lua_pushstring(L, "F10");
	lua_pushinteger(L, KEYCODE_F10);
	lua_settable(L, 1);

	lua_pushstring(L, "F11");
	lua_pushinteger(L, KEYCODE_F11);
	lua_settable(L, 1);

	lua_pushstring(L, "F12");
	lua_pushinteger(L, KEYCODE_F12);
	lua_settable(L, 1);

	lua_pushstring(L, "Backtick");
	lua_pushinteger(L, KEYCODE_BACKTICK);
	lua_settable(L, 1);

	lua_pushstring(L, "Tab");
	lua_pushinteger(L, KEYCODE_TAB);
	lua_settable(L, 1);

	lua_pushstring(L, "LeftMouse");
	lua_pushinteger(L, KEYCODE_LEFTMOUSE);
	lua_settable(L, 1);

	lua_pushstring(L, "MiddleMouse");
	lua_pushinteger(L, KEYCODE_MIDDLEMOUSE);
	lua_settable(L, 1);

	lua_pushstring(L, "RightMouse");
	lua_pushinteger(L, KEYCODE_RIGHTMOUSE);
	lua_settable(L, 1);

	lua_pushstring(L, "Escape");
	lua_pushinteger(L, KEYCODE_ESCAPE);
	lua_settable(L, 1);

	return 1;
}

int LuaHostFunctions::l_GetDeltaTime(lua_State* L)
{
	return 0;
}

int LuaHostFunctions::l_ActorNew(lua_State* L)
{
	LuaLevel* level = LuaLevel::instance;

	if (!level)
		throw(std::runtime_error("Level instance was nullptr."));

	std::string name = lua_tostring(L, 1);
	std::string tag = lua_tostring(L, 2);

	Actor* actor = new Actor(name, tag);

	level->actors.push_back(actor);

	lua_pushinteger(L, (unsigned int)actor);

	return 1;
}

int LuaHostFunctions::l_ActorAddComponent(lua_State* L)
{
	lua_settop(L, 2);

	ComponentType comptype = (ComponentType)luaL_checkinteger(L, -1);
	Actor* actor = (Actor*)luaL_checkinteger(L, -2);

	unsigned int ptr = 0;

	switch (comptype)
	{
	case(ComponentType::RECTRENDERER):
		ptr = (unsigned int)actor->AddComponent<RectRenderer>();
		break;
	case(ComponentType::ELLIPSERENDERER):
		ptr = (unsigned int)actor->AddComponent<EllipseRenderer>();
		break;
	case(ComponentType::SPRITERENDERER):
		ptr = (unsigned int)actor->AddComponent<SpriteRenderer>();
		break;
	case(ComponentType::TEXTRENDERER):
		ptr = (unsigned int)actor->AddComponent<TextRenderer>();
		break;
	case(ComponentType::PHYSICSOBJECT):
		ptr = (unsigned int)actor->AddComponent<PhysicsObject>();
		break;
	case(ComponentType::ANIMATION):
		ptr = (unsigned int)actor->AddComponent<Animation>();
		break;
	case(ComponentType::AUDIOSOURCE):
		ptr = (unsigned int)actor->AddComponent<AudioSource>();
		break;
	}

	lua_pushinteger(L, ptr);

	return 1;
}

int LuaHostFunctions::l_ActorGetComponent(lua_State* L)
{
	lua_settop(L, 2);

	luaL_checktype(L, 1, LUA_TTABLE);

	ComponentType t = (ComponentType)luaL_checkinteger(L, 2);

	lua_pop(L, 1);

	lua_getfield(L, 1, "_handle");

	Actor* actor = (Actor*)luaL_checkinteger(L, 2);

	unsigned int ptr = 0;

	switch (t)
	{
	case(ComponentType::RECTRENDERER):
		ptr = (unsigned int)actor->GetComponent<RectRenderer>();
		break;
	case(ComponentType::ELLIPSERENDERER):
		ptr = (unsigned int)actor->GetComponent<EllipseRenderer>();
		break;
	case(ComponentType::SPRITERENDERER):
		ptr = (unsigned int)actor->GetComponent<SpriteRenderer>();
		break;
	case(ComponentType::TEXTRENDERER):
		ptr = (unsigned int)actor->GetComponent<TextRenderer>();
		break;
	case(ComponentType::PHYSICSOBJECT):
		ptr = (unsigned int)actor->GetComponent<PhysicsObject>();
		break;
	case(ComponentType::ANIMATION):
		ptr = (unsigned int)actor->GetComponent<Animation>();
		break;
	case(ComponentType::AUDIOSOURCE):
		ptr = (unsigned int)actor->GetComponent<AudioSource>();
		break;
	}

	lua_pushinteger(L, ptr);

	return 1;

}

int LuaHostFunctions::l_ActorRemoveComponent(lua_State* L)
{
	lua_settop(L, 2);

	luaL_checktype(L, 1, LUA_TTABLE);

	ComponentType t = (ComponentType)luaL_checkinteger(L, 2);

	lua_pop(L, 1);

	lua_getfield(L, 1, "_handle");

	Actor* actor = (Actor*)luaL_checkinteger(L, 2);

	unsigned int ptr = 0;

	switch (t)
	{
	case(ComponentType::RECTRENDERER):
		ptr = (unsigned int)actor->GetComponent<RectRenderer>();
		actor->RemoveComponent<RectRenderer>();
		break;
	case(ComponentType::ELLIPSERENDERER):
		ptr = (unsigned int)actor->GetComponent<EllipseRenderer>();
		actor->RemoveComponent<EllipseRenderer>();
		break;
	case(ComponentType::SPRITERENDERER):
		ptr = (unsigned int)actor->GetComponent<SpriteRenderer>();
		actor->RemoveComponent<SpriteRenderer>();
		break;
	case(ComponentType::TEXTRENDERER):
		ptr = (unsigned int)actor->GetComponent<TextRenderer>();
		actor->RemoveComponent<TextRenderer>();
		break;
	case(ComponentType::PHYSICSOBJECT):
		ptr = (unsigned int)actor->GetComponent<PhysicsObject>();
		actor->RemoveComponent<PhysicsObject>();
		break;
	case(ComponentType::ANIMATION):
		ptr = (unsigned int)actor->GetComponent<Animation>();
		actor->RemoveComponent<Animation>();
		break;
	case(ComponentType::AUDIOSOURCE):
		ptr = (unsigned int)actor->GetComponent<AudioSource>();
		actor->RemoveComponent<AudioSource>();
		break;
	}

	lua_pushinteger(L, ptr);

	return 1;
}

int LuaHostFunctions::l_ActorDestroy(lua_State* L)
{
	Actor* actor = (Actor*)lua_tointeger(L, 1);

	int index = 0;
	LuaLevel* level = LuaLevel::instance;

	for (Actor* a : level->actors)
	{
		if (a == actor) break;
		index++;
	}

	level->actors.erase(level->actors.begin() + index);

	delete actor;
	
	return 0;
}

int LuaHostFunctions::l_ActorUpdate(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TTABLE);

	// simple members

	lua_getfield(L, 1, "_handle");
	lua_getfield(L, 1, "name");
	lua_getfield(L, 1, "tag");
	
	Actor* actor = (Actor*)luaL_checkinteger(L, 2);
	std::string name = luaL_checkstring(L, 3);
	std::string tag = luaL_checkstring(L, 4);

	lua_pop(L, 3);

	// table members

	lua_getfield(L, 1, "transform");

	lua_getfield(L, 2, "position");

	Vector2D pos = GetVector2D(L);

	lua_getfield(L, 2, "rotation");

	float rot = (float)luaL_checknumber(L, -1);

	actor->name = name;
	actor->tag = tag;

	actor->transform.position = pos;
	actor->transform.rotation = rot;

	return 0;
}

int LuaHostFunctions::l_ComponentUpdate(lua_State* L)
{
	lua_settop(L, 1);

	luaL_checktype(L, 1, LUA_TTABLE);

	lua_getfield(L, 1, "enabled");
	lua_getfield(L, 1, "_handle");

	Component* comp = (Component*)luaL_checkinteger(L, -1);

	luaL_checktype(L, -2, LUA_TBOOLEAN);

	comp->enabled = lua_toboolean(L, -2);

	lua_pop(L, 2);

	return 0;
}

int LuaHostFunctions::l_RendererUpdate(lua_State* L)
{

	lua_settop(L, 1);
	luaL_checktype(L, 1, LUA_TTABLE);

	lua_getfield(L, 1, "priority");
	lua_getfield(L, 1, "_handle");

	Renderer* rend = (Renderer*)luaL_checkinteger(L, -1);

	rend->priority = luaL_checkinteger(L, -2);

	lua_pop(L, 2);

	lua_getfield(L, 1, "scale");

	rend->scale = GetVector2D(L);

	return 0;

}

int LuaHostFunctions::l_RectRendererUpdate(lua_State* L)
{
	lua_settop(L, 1);
	luaL_checktype(L, 1, LUA_TTABLE);

	lua_getfield(L, 1, "_handle");
	lua_getfield(L, 1, "width");
	lua_getfield(L, 1, "height");

	RectRenderer* renderer = (RectRenderer*)luaL_checkinteger(L, 2);
	
	renderer->width = (float)luaL_checknumber(L, 3);
	renderer->height = (float)luaL_checknumber(L, 4);
	
	lua_pop(L, 3);

	lua_getfield(L, 1, "colour");

	renderer->colour = GetColour(L);

	lua_pop(L, 1);

	return 0;

}

int LuaHostFunctions::l_EllipseRendererUpdate(lua_State* L)
{

	lua_settop(L, 1);

	luaL_checktype(L, 1, LUA_TTABLE);

	lua_getfield(L, 1, "_handle");

	EllipseRenderer* renderer = (EllipseRenderer*)luaL_checkinteger(L, 2);

	lua_pop(L, 1);

	lua_getfield(L, 1, "colour");

	renderer->colour = GetColour(L);

	lua_pop(L, 1);

	lua_getfield(L, 1, "radii");

	Vector2D radii = GetVector2D(L);

	lua_pop(L, 1);

	renderer->radiusX = radii.x;
	renderer->radiusY = radii.y;

	return 0;

}

int LuaHostFunctions::l_SpriteRendererUpdate(lua_State* L)
{
	return 0;
}

int LuaHostFunctions::l_SpriteRendererGetSprite(lua_State* L)
{

	lua_settop(L, 1);

	luaL_checktype(L, 1, LUA_TTABLE);

	lua_getfield(L, 1, "_handle");

	SpriteRenderer* rend = (SpriteRenderer*)luaL_checkinteger(L, -1);

	lua_pop(L, 1);

	Sprite* s = rend->GetSprite();

	if (s == nullptr)
	{
		lua_pushnil(L);
		return 1;
	}
	else
	{

		std::wstring path = s->GetPath();

		//setup converter
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;

		//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
		std::string converted = converter.to_bytes(path);

		lua_pushstring(L, converted.c_str());

		return 1;

	}

}

int LuaHostFunctions::l_SpriteRendererSetSprite(lua_State* L)
{

	lua_settop(L, 2);

	if (!lua_isnil(L, -1))
	{
		std::string path = luaL_checkstring(L, -1);

		lua_pop(L, 1);

		luaL_checktype(L, -1, LUA_TTABLE);

		lua_getfield(L, -1, "_handle");

		SpriteRenderer* rend = (SpriteRenderer*)luaL_checkinteger(L, -1);

		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;

		std::wstring converted = converter.from_bytes(path);
		Sprite* s;
		try
		{
			s = Sprite::LoadSprite(converted);
		}
		catch (...)
		{
			throw std::runtime_error(std::string("Couldn't find the file ") + path);
		}
		rend->SetSprite(s);
	}
	else
	{
		lua_pop(L, 1);
		lua_getfield(L, -1, "_handle");
		SpriteRenderer* rend = (SpriteRenderer*)luaL_checkinteger(L, -1);

		rend->SetSprite(nullptr);

	}

	return 0;

}

Vector2D LuaHostFunctions::GetVector2D(lua_State * L)
{
	luaL_checktype(L, -1, LUA_TTABLE);

	lua_getfield(L, -1, "x");
	lua_getfield(L, -2, "y");

	float x = (float)luaL_checknumber(L, -2), y = (float)luaL_checknumber(L, -1);

	lua_pop(L, 2);

	return Vector2D(x, y);
}

Colour LuaHostFunctions::GetColour(lua_State * L)
{
	luaL_checktype(L, -1, LUA_TTABLE);
	
	lua_getfield(L, -1, "r");
	lua_getfield(L, -2, "g");
	lua_getfield(L, -3, "b");
	lua_getfield(L, -4, "a");

	float r = (float)luaL_checknumber(L, -4), g = (float)luaL_checknumber(L, -3), b = (float)luaL_checknumber(L, -2), a = (float)luaL_checknumber(L, -1);

	lua_pop(L, 4);

	return Colour(r, g, b, a);

}
