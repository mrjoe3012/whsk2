#pragma once
#include "Colour.h"
#include <string>

namespace Engine
{
	struct EngineConfig
	{
		int windowWidth;
		int windowHeight;
		int physicsLayerCount;

		Colour backgroundColour;

		std::string firstLevel;
		std::string windowTitle;

		bool debug;
	};
}