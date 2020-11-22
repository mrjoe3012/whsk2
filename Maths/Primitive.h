#pragma once
#include "Vector2D.h"

using Engine::Maths::Vector2D;

namespace Engine
{
	namespace Maths
	{
		class Primitive
		{
		public:
			Primitive(Vector2D center, float rotation);
			Primitive(Vector2D center) : Primitive(center, 0.0f) {}
			Primitive();
			virtual ~Primitive();

			Vector2D center; 
			float rotation; 
			virtual bool Contains(Vector2D point) const = 0; 
		};
	}
}