#include "Vector2D.h"
#include "Matrix.h"
#include "Maths.h"

using Engine::Maths::Vector2D;

Vector2D::Vector2D()
	:
	Vector2D(0.0f, 0.0f)
{

}

Vector2D::Vector2D(float x, float y)
	:
	x(x),
	y(y)
{

}

Vector2D::~Vector2D()
{

}

Vector2D Vector2D::operator+(const Vector2D& rhs) const
{
	Vector2D result = *this;
	result.x += rhs.x;
	result.y += rhs.y;
	return result;
}

Vector2D Vector2D::operator-(const Vector2D& rhs) const
{
	Vector2D result = *this;
	result.x -= rhs.x;
	result.y -= rhs.y;
	return result;
}

Vector2D Vector2D::operator*(float rhs) const
{
	Vector2D v = *this;
	v.x *= rhs;
	v.y *= rhs;

	return v;
}

Vector2D Vector2D::operator/(float rhs) const
{
	Vector2D v = *this;

	v.x /= rhs;
	v.y /= rhs;

	return v;
}

void Vector2D::operator*=(float rhs)
{
	*this = (*this * rhs);
}

void Vector2D::operator/=(float rhs)
{
	*this = (*this / rhs);
}

void Vector2D::operator+=(const Vector2D& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
}

Vector2D Engine::Maths::operator*(float lhs, const Vector2D& rhs)
{
	return rhs * lhs;
}

bool Vector2D::operator==(const Vector2D& rhs) const
{
	return ((rhs.x >= this->x - 0.01 && rhs.x <= this->x + 0.01) && (rhs.y >= this->y - 0.01 && rhs.y <= this->y + 0.01));
}

bool Vector2D::operator!=(const Vector2D& rhs) const
{
	return !(*this == rhs);
}

float Vector2D::Magnitude() const
{
	// Root of square magnitude.
	return sqrt(SquareMagnitude());
}

float Vector2D::SquareMagnitude() const
{
	// Square magnitude using components -> |v|^2 = x^2 + y^2 / a^2 = b^2 + c^2
	return powf(x, 2.0f) + powf(y, 2.0f);
}

Vector2D Vector2D::RotatePoint(Vector2D pivot, Vector2D point, float angle)
{
	
	Matrix<float> transform = TranslationMatrix(point);
	Matrix<float> pivotTransform = TranslationMatrix(pivot);

	Matrix<float> rotationMatrix = RotationMatrix(angle);

	transform -= pivotTransform;
	transform = rotationMatrix * transform;
	transform += pivotTransform;

	float x = transform[0][0], y = transform[1][0];

	Vector2D image = Vector2D(x, y);

	return image;
}

Vector2D Vector2D::AddRotation(Vector2D pivot, Vector2D point, float rotation) // Adds passed rotation to current rotation around pivot point
{

	float currentRot = Vector2D::Angle((point - pivot), Vector2D(0.0f,1.0f)); // Get the angle between point to pivot and y-axis

	if (point.x < pivot.x) currentRot = 360 - currentRot; // If the point is behind the y-axis, use the longest angle.

	return Vector2D::RotatePoint(pivot, point, currentRot + rotation);

}

float Vector2D::Angle(Vector2D a, Vector2D b) // Returns the smallest angle between a and b
{
	float dotProduct = Vector2D::ScalarProduct(a, b);
	float angleRadians = acosf(dotProduct / (a.Magnitude()*b.Magnitude())); // cosx = (a.b)/(|a|*|b|)
	if (isnan(angleRadians)) angleRadians = 0;

	return angleRadians;
}

float Vector2D::ScalarProduct(Vector2D a, Vector2D b) // Returns a.b
{
	return (a.x*b.x) + (a.y*b.y);
}

Vector2D Vector2D::Normalize(Vector2D v) // Normalizes vector: v(normalized) = (1/|v|)*v
{
	if (v.Magnitude() != 0)
		return (1.0f / v.Magnitude()) * v;
	else
	{
		return v;
	}
}