#pragma once

namespace Engine
{

	namespace Maths
	{

		struct Equation
		{
		public:
			Equation();
			~Equation();

			struct EquationVariable
			{

			public:
				EquationVariable();
				EquationVariable(float, float);
				~EquationVariable();
				float coefficient;
				float exponent;

			};

		};

	}

}