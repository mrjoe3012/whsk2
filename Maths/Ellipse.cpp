#include "Ellipse.h"
#include "Maths.h"

using Engine::Maths::Ellipse;
using Engine::Maths::Vector2D;

Ellipse::Ellipse(Vector2D center, Vector2D radii)
	:
	Primitive(center, 0),
	radii(radii)
{

}

Ellipse::Ellipse()
	:
	Primitive(),
	radii()
{

}

Ellipse::~Ellipse()
{

}

std::vector<int> Ellipse::GetX(int y) const // Rotation ignored, returns the corresponding xValues with passed y value.
{
	std::vector<int> results = std::vector<int>();

	int eqtnSquared = ((pow((int)radii.x, 2))*(1 - (pow(y - (int)center.y, 2) / pow((int)radii.y, 2)))); // The value of the equation squared before adding the constant.
																										 // used to check the roots of the equation, (real, equal), (real, distinct), (unreal)

	if (eqtnSquared == 0) // The roots are equal and so there is only one value.
	{
		results.push_back((int)center.x);
	}
	else if (eqtnSquared > 0) // The roots are real and distinct and so there are two values
	{
		results.push_back(sqrt(eqtnSquared) + (int)center.x);
		results.push_back((-sqrt(eqtnSquared)) + (int)center.x);
	}


	return results;
}


std::vector<int> Ellipse::GetY(int x) const // Rotation ignored, returns the corresponding yValues with passed x value.
{
	std::vector<int> results = std::vector<int>();

	int eqtnSquared = (pow((int)radii.y, 2)) * (1 - (pow(x - (int)center.x, 2) / pow((int)radii.x, 2)));

	if (eqtnSquared == 0)
	{
		results.push_back((int)center.y);
	}
	else if (eqtnSquared > 0)
	{
		results.push_back(sqrt(eqtnSquared) + (int)center.y);
		results.push_back((-sqrt(eqtnSquared)) + (int)center.y);
	}

	return results;
}

bool Ellipse::Contains(Vector2D point) const
{

	point = Vector2D::RotatePoint(center, point, -rotation);

	int xValueCount = 0, yValueCount = 0;

	std::vector<int> xVals = Ellipse::GetX(point.y);
	std::vector<int> yVals = Ellipse::GetY(point.x);

	xValueCount = xVals.size();
	yValueCount = yVals.size();

	if (xValueCount == 0 || yValueCount == 0) // Point cannot be in the ellipse as no boundaries are in either direction.
		return false;
	else if (xValueCount + yValueCount == 4) // Point lies inside of the ellipse as boundaries exist on all sides of the point.
		return true;
	else if (xValueCount == 2 || yValueCount == 2 && !(xValueCount == 2 && yValueCount == 2)) // Point must be inside of ellipse as at least one value exists for 
		return true;																		  // both x and y and either x or y has two one value meaning the point lies on the ellipse.
	else
		return false;

}