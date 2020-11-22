#include "Circle.h"

using Engine::Maths::Circle;

Circle::Circle(Vector2D center, float radius)
	:
	Primitive(center),
	radius(radius)
{

}

Circle::Circle()
	:
	Primitive(),
	radius(1)
{

}

Circle::~Circle()
{

}

Ellipse Circle::GetEllipse() const
{
	return Ellipse(center, Vector2D(radius, radius));
}

bool Circle::Contains(Vector2D point) const
{
	return GetEllipse().Contains(point);
}

bool Circle::operator==(const Circle& const rhs) const
{
	return ((rhs.center == center) && (rhs.radius == radius));
}