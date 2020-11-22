#include "Primitive.h"

using Engine::Maths::Primitive;

Primitive::Primitive(Vector2D center, float rotation)
	:
	center(center),
	rotation(rotation)
{

}

Primitive::Primitive()
	:
	center()
{

}

Primitive::~Primitive()
{

}