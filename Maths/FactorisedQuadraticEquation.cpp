#include "FactorisedQuadraticEquation.h"
#include "Maths.h"

using Engine::Maths::FactorisedQuadraticEquation;
using Engine::Maths::ExpandedQuadraticEquation;
using Engine::Maths::BinomialExpression;
typedef  Engine::Maths::Equation::EquationVariable EquationVariable;
typedef Engine::Maths::QuadraticEquation::QuadraticRootsInfo QuadraticRootsInfo;

FactorisedQuadraticEquation::FactorisedQuadraticEquation(BinomialExpression expression)
	:
	expression1(expression),
	expression2(expression)
{

}

FactorisedQuadraticEquation::FactorisedQuadraticEquation(BinomialExpression expression1, BinomialExpression expression2)
	:
	expression1(expression1),
	expression2(expression2)
{

}

FactorisedQuadraticEquation::FactorisedQuadraticEquation()
{

}

FactorisedQuadraticEquation::~FactorisedQuadraticEquation()
{

}

QuadraticRootsInfo FactorisedQuadraticEquation::Roots() const
{
	QuadraticRootsInfo res = Expand().Roots();
	return res;
}

ExpandedQuadraticEquation FactorisedQuadraticEquation::Expand() const
{
	float xSquaredCoef = expression1.x*expression2.x;
	float xCoef = (expression1.x*expression2.constant) + (expression1.constant*expression2.x);
	float constant = expression1.constant*expression2.constant;

	ExpandedQuadraticEquation result(EquationVariable(xSquaredCoef, 1), EquationVariable(xCoef, 1), EquationVariable(constant, 1));
	return result;
}