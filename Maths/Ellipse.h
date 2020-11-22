#pragma once
#include "Primitive.h"
#include "Vector2D.h"
#include <vector>

using Engine::Maths::Primitive;
using Engine::Maths::Vector2D;

namespace Engine
{
	namespace Maths
	{
		class Ellipse : public Primitive // Represents an ellipse
		{

		public:
			Ellipse(Vector2D center, Vector2D radii);
			Ellipse();
			~Ellipse();

			Vector2D radii; // Vector holds 2 radii for x and y.

			bool Contains(Vector2D) const override;

			std::vector<int> GetX(int y) const; 
			std::vector<int> GetY(int x) const; 
		};
	}
}