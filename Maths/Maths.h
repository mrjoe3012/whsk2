#pragma once
#define WHSK_EPSILON 0.001f
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector2D.h"
#include "Line.h"
#include "Matrix.h"
#include "IntersectionInfo.h"
#include "Rect.h"
#include "Circle.h"

namespace Engine
{

	namespace Maths
	{

		Matrix<float> RotationMatrix(float angle);

		Matrix<float> TranslationMatrix(Vector2D displacement);

		Matrix<float> ScalingMatrix(Vector2D scale);

		float Radians(float degrees);
		float Degrees(float radians);

		bool IsZero(float val);

		IntersectionInfo CheckIntersection(Rect& r1, Rect& r2);
		IntersectionInfo CheckIntersection(Rect& r, Line& l);
		IntersectionInfo CheckIntersection(Line& l1, Line& l2);
		IntersectionInfo CheckIntersection(Circle& c1, Circle& c2);
		IntersectionInfo CheckIntersection(Line& l, Circle& c);
		IntersectionInfo CheckIntersection(Rect& r, Circle& c);
		//IntersectionInfo* CheckIntersection(Ellipse& e1, Ellipse& e2);

	}

}