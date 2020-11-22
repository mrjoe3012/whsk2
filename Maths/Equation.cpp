#include "Equation.h"

using Engine::Maths::Equation;

Equation::Equation()
{

}

Equation::~Equation()
{

}

Equation::EquationVariable::EquationVariable()
	:
	EquationVariable(0, 0)
{

}

Equation::EquationVariable::EquationVariable(float coef, float exp)
	:
	coefficient(coef),
	exponent(exp)
{

}

Equation::EquationVariable::~EquationVariable()
{

}