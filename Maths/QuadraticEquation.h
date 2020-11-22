#pragma once
#include "Equation.h"

namespace Engine
{
	namespace Maths
	{
		struct QuadraticEquation : public Equation
		{
		public:
			QuadraticEquation();
			~QuadraticEquation();

			struct QuadraticRootsInfo
			{
			public:
				QuadraticRootsInfo();
				QuadraticRootsInfo(float discriminant, float root);
				QuadraticRootsInfo(float discriminant, float root1, float root2);
				~QuadraticRootsInfo();

				float discriminant; // If discriminant > 0 then roots = +-roots, if == 0 then roots = roots, if disciminant < 0 roots = nan;
				float root1, root2;
			};

			virtual QuadraticRootsInfo Roots() const = 0;
		};
	}
}