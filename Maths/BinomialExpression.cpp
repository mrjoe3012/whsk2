#include "BinomialExpression.h"

using Engine::Maths::BinomialExpression;

BinomialExpression::BinomialExpression(float x, float constant, float exponent)
	:
	x(x),
	constant(constant),
	exponent(exponent)
{

}

BinomialExpression::BinomialExpression()
	:
	x(0),
	constant(0),
	exponent(0)
{

}

BinomialExpression::~BinomialExpression()
{

}