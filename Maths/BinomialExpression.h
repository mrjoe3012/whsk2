#pragma once
#include "Equation.h"

namespace Engine
{
	namespace Maths
	{

		struct BinomialExpression
		{

		public:
			BinomialExpression();
			BinomialExpression(float x, float constant, float exponent);
			~BinomialExpression();
			float x, constant, exponent;
		};

	}
}