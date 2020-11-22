#pragma once
#include "Primitive.h"
#include <vector>
#include "Line.h"

using Engine::Maths::Primitive;
using Engine::Maths::Line;

namespace Engine
{
	namespace Maths
	{

		class Rect : public Primitive
		{
		public:
			Rect(Vector2D center, float width, float height);
			Rect(Vector2D center, float width, float height, float rotation);
			Rect();
			~Rect();

			bool Contains(Vector2D point) const override;

			float width, height;

			Line Top();
			Line Right();
			Line Bottom();
			Line Left();
			std::vector<Line> GetLines();
		};

	}
}