#pragma once

#include "Level.h"
#include "LuaManager.h"
#include "Actor.h"

namespace Engine
{

	class LuaLevel : public Level
	{
	private:
		std::string filename;


	public:
		std::vector<Actor*> actors;
		static LuaLevel* instance;

		LuaLevel(std::string filename);
		~LuaLevel();

		void OnLoad() override;
		void OnUnload() override;
		void OnQuit(int code) override;
		void Update() override;
	};

}