#pragma once
#include "Vector.h"

namespace Engine
{

	namespace Maths
	{

		class Vector2D : public Vector
		{

		public:
			Vector2D(); // Initialises with 0,0
			Vector2D(float x, float y); // Initialises with parameters.
			~Vector2D();

			Vector2D operator+(const Vector2D& rhs) const;
			Vector2D operator-(const Vector2D& rhs) const;
			Vector2D operator*(float rhs) const;
			Vector2D operator/(float rhs) const;
			void operator*=(float rhs);
			void operator/=(float rhs);
			void operator+=(const Vector2D& rhs);
			bool operator==(const Vector2D& rhs) const;
			bool operator!=(const Vector2D& rhs) const;

			friend Vector2D operator*(float lhs, const Vector2D& rhs);

			float x; // The x component of the vector;
			float y; // The y component of the vector;
			float Magnitude() const override; // Returns |v| -> sqrt(x^2+y^2)
			float SquareMagnitude() const override; // Returns (|v|)^2 -> x^2+y^2

			static Vector2D RotatePoint(Vector2D pivot, Vector2D point, float angle); // Rotates a line and returns the new end point. Angle is in relation to the positive y-axis clockwise.
			static Vector2D AddRotation(Vector2D pivot, Vector2D point, float rotation); // Rotates a line by its current rotation + passed rotation and returns the end point.
			static Vector2D Normalize(Vector2D v); // Returns a normalized vector
			static float ScalarProduct(Vector2D a, Vector2D b); // Returns the scalar product of two vectors.
			static float Angle(Vector2D a, Vector2D b); // Returns the smallest angle between the two vectors in radians.
		};

	}

}