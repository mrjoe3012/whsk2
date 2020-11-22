#include "Maths.h"
#include "ExpandedQuadraticEquation.h"
#include "FactorisedQuadraticEquation.h"
#include "BinomialExpression.h"

using namespace Engine::Maths;

Matrix<float> Engine::Maths::RotationMatrix(float angle) // anticlockwise radians
{
	Matrix<float> mat = Matrix<float>(2, 2, { cos(angle), -sin(angle), sin(angle), cos(angle) });
	return mat;
}

Matrix<float> Engine::Maths::TranslationMatrix(Vector2D displacement) // translation/transformation matrix
{
	Matrix<float> mat = Matrix<float>(2, 1, { displacement.x, displacement.y });
	return mat;
}

Matrix<float> Engine::Maths::ScalingMatrix(Vector2D scale)
{
	Matrix<float> mat = Matrix<float>(2, 2, { scale.x, 0, 0, scale.y });
	return mat;
}

float Engine::Maths::Degrees(float radians)
{
	float degrees = (radians*180.0f) / M_PI;
	return degrees;
}

float Engine::Maths::Radians(float degrees)
{
	float radians = (degrees*M_PI) / 180.0f;
	return radians;
}

IntersectionInfo Engine::Maths::CheckIntersection(Line& l1, Line& l2)
{
	IntersectionInfo info = IntersectionInfo();

	if (l1 == l2) // Lines are perfectly identical
	{
		info.identical = true;
		return info;
	}


	if (isnan(l1.Gradient()) && isnan(l2.Gradient())) // Both gradients are undefined and both vertical lines.
	{
		if (l1.begin.x == l2.begin.x)
		{
			Line line1, line2; // Temporary vars

			line1 = l1.LineVector().y < 0 ? Line(l1.end, l1.begin) : l1; // If the line is going downwards, flip it so that both are going upwards.
			line2 = l2.LineVector().y < 0 ? Line(l2.end, l2.begin) : l2;

			Line lineOnTop = line1.begin.y < line2.begin.y ? line2 : line1; // Find out which line starts furthest up.

			info.pointsOfIntersection = { Vector2D(lineOnTop.begin) }; // Intersects where the overlapping line begins.
			return info;
		}
	}
	else if ((isnan(l1.Gradient()) || isnan(l2.Gradient()))) // If only one line has an undefined gradient
	{
		float x = isnan(l1.Gradient()) ? l1.begin.x : l2.begin.x; // Set the x value to the x value of the line with the undefined gradient.
		float y = isnan(l1.Gradient()) ? l2.GetY(x) : l1.GetY(x); // Set the y value to the corresponding point on the line that has a real gradient.

		info.pointsOfIntersection = { Vector2D(x, y) };
		return info;
	}

	auto checkPoint = [&l1, &l2](Vector2D point)
	{
		return (point.x >= l1.begin.x && point.x <= l1.end.x && point.x >= l2.begin.x && point.x <= l2.end.x);
	};



	Matrix<float> lines = Matrix<float>(2, 2, { 1, -l1.Gradient(), 1, -l2.Gradient() });
	Matrix<float> offsets = Matrix<float>(2, 1, { l1.ConstantOffset(), l2.ConstantOffset() });
	
	float det = lines.Determinant();

	if (IsZero(det))
	{
		return info;
	}

	Matrix<float> solution = lines.Inverse() * offsets;

	Vector2D point = Vector2D(solution[0][0], solution[1][0]);
	if (checkPoint(point))
	{
		info.pointsOfIntersection = { point };
	}

	return info;
}

IntersectionInfo Engine::Maths::CheckIntersection(Rect& r, Line& l)
{

	IntersectionInfo possiblePoints = IntersectionInfo();

	IntersectionInfo temp;
	Line l2;
	// Check if each of the lines of the rectangle intersect with l. Add the points of intersection to possiblePoints and return it.
	l2 = r.Top();
	temp = CheckIntersection(l, l2);

	(possiblePoints) += (temp);

	l2 = r.Right();
	temp = CheckIntersection(l, l2);

	possiblePoints += temp;

	l2 = r.Bottom();
	temp = CheckIntersection(l, l2);

	possiblePoints += temp;

	l2 = r.Left();
	temp = CheckIntersection(l, l2);

	possiblePoints += temp;

	return possiblePoints;

}

IntersectionInfo Engine::Maths::CheckIntersection(Rect& r1, Rect& r2)
{
	std::vector<Line> r2Lines = r2.GetLines();

	IntersectionInfo possiblePoints = IntersectionInfo();
	// Get points of intersection between this rectangle and every line that belongs to r2.
	for (size_t i = 0; i < 4; i++)
	{

		possiblePoints += CheckIntersection(r1, r2Lines[i]);

	}

	return possiblePoints;

}


IntersectionInfo Engine::Maths::CheckIntersection(Circle& c1, Circle& c2)
{
	IntersectionInfo info = IntersectionInfo();

	if (c1 == c2) // Check if the circles are identical
	{
		info.identical = true;
		return info;
	}

	if ((c1.center - c2.center).Magnitude() < c1.radius + c2.radius && (c1.center != c2.center)) // Must collide as distance between centers is <= than sum of radii
	{

		// Finding the radical line

		// (x-h)^2+(y-k)^2-r^2=0

		ExpandedQuadraticEquation xRes, yRes;

		FactorisedQuadraticEquation c1X, c1Y; // (x-h)^2 and (y-k)^2
		FactorisedQuadraticEquation c2X, c2Y;

		c1X = FactorisedQuadraticEquation(BinomialExpression(1, -c1.center.x, 2)); // (x-h)^2
		c1Y = FactorisedQuadraticEquation(BinomialExpression(1, -c1.center.y, 2)); // (y-k)^2

		c2X = FactorisedQuadraticEquation(BinomialExpression(1, -c2.center.x, 2)); // (x-h)^2
		c2Y = FactorisedQuadraticEquation(BinomialExpression(1, -c2.center.y, 2)); // (y-k)^2

		xRes = c1X.Expand() - c2X.Expand(); // coefficients of the 2nd degree will be zero always: (x-b)^2=(x-a)^ -> x^2-2xb-b^2=x^2-2xa-a^2 -> x^2-x^2...
		yRes = c1Y.Expand() - c2Y.Expand();

		ExpandedQuadraticEquation radicalLine;

		radicalLine.constant.coefficient = xRes.constant.coefficient + yRes.constant.coefficient; // 1) ax + b 2) cy + d | k = b-d
		radicalLine.constant.coefficient += -powf(c1.radius, 2) + powf(c2.radius, 2);
		radicalLine.x.coefficient = xRes.x.coefficient;
		radicalLine /= -yRes.x.coefficient; // ay = mx + c -> y = (mx+c) / a


		// Using the radical line to find x position of points of intersection.
		// Substitute y=mx+c into r^2=(x-h)^2+(y-h)^2
		// -> r^2=(x-h)^2+(mx+c-h)^2


		ExpandedQuadraticEquation circleEquatedToRadicalLine;
		// Check if radical line has a real gradient
		if ((!isnan(radicalLine.x.coefficient) && !isinf(radicalLine.x.coefficient)) && (!isnan(radicalLine.constant.coefficient) && !isinf(radicalLine.constant.coefficient)))
		{
			circleEquatedToRadicalLine = FactorisedQuadraticEquation(BinomialExpression(1, -c1.center.x, 2)).Expand() + FactorisedQuadraticEquation(BinomialExpression(radicalLine.x.coefficient, radicalLine.constant.coefficient - c1.center.y, 2)).Expand();
			circleEquatedToRadicalLine.constant.coefficient -= powf(c1.radius, 2);

			auto roots = circleEquatedToRadicalLine.Roots();

			if (roots.discriminant == 0) // This should never happen, but just in case we will return a root
			{
				float y = (radicalLine.x.coefficient * roots.root1) + radicalLine.constant.coefficient;

				info.pointsOfIntersection.push_back(Vector2D(roots.root1, y));
			}
			else
			{
				float y1 = 0, y2 = 0;
				y1 = (radicalLine.x.coefficient * roots.root1) + radicalLine.constant.coefficient; // Find the point on the line with the x position from the roots.
				y2 = (radicalLine.x.coefficient * roots.root2) + radicalLine.constant.coefficient;

				info.pointsOfIntersection = { Vector2D(roots.root1, y1), Vector2D(roots.root2, y2) };
			}
		}
		else
		{
			// If no real gradient, revert radical line back to linear form (y=x)
			radicalLine.constant.coefficient = xRes.constant.coefficient + yRes.constant.coefficient; // 1) ax + b 2) cy + d | k = b-d
			radicalLine.constant.coefficient += -powf(c1.radius, 2) + powf(c2.radius, 2);
			radicalLine.x.coefficient = xRes.x.coefficient;
			// Get x value
			float x = radicalLine.constant.coefficient / radicalLine.x.coefficient;
			// Get two yValues if not then do nothing
			std::vector<int> yValues = c1.GetEllipse().GetY(x);

			if (yValues.size() > 0)
			{
				if (yValues.size() == 2)
					info.pointsOfIntersection = { Vector2D(x,yValues[0]), Vector2D(x,yValues[1]) };
				else
					info.pointsOfIntersection = { Vector2D(x,yValues[0]) };
			}

		}

	}
	else if ((c1.center - c2.center).Magnitude() == c1.radius + c2.radius && (c1.center != c2.center)) // Special case 1 point of intersection
	{
		Line c1c2 = Line(c1.center, c2.center);
		Vector2D v = Vector2D::Normalize(c1c2.LineVector());

		v *= c1.radius;

		Vector2D point = c1.center + v;

		info.pointsOfIntersection = { point };

	}

	return info;
}

IntersectionInfo Engine::Maths::CheckIntersection(Line& l, Circle& c)
{
	IntersectionInfo info = IntersectionInfo();

	float m = l.Gradient();
	float coff = l.ConstantOffset();
	
	float A = (m + 1);
	float B = (2 * m*coff) - (2 * c.center.x) - (2 * c.center.y*m);
	float C = (-2 * c.center.y*coff) + powf(c.center.y, 2.0f) + powf(c.center.x, 2.0f) + powf(coff, 2.0f) - powf(c.radius, 2.0f);
	float discriminant = powf(B, 2.0f) - (4 * A*C);

	auto checkPoint = [&l](Vector2D point)
	{
		return (point.x >= l.begin.x && point.x <= l.end.x);
	};

	if (discriminant > 0)
	{
		float x1 = ((-B) + sqrtf(discriminant)) / (2 * A);
		float x2 = ((-B) - sqrtf(discriminant)) / (2 * A);
		float y1 = l.GetY(x1);
		float y2 = l.GetY(x2);

		Vector2D point1 = Vector2D(x1, y1), point2 = Vector2D(x2, y2);

		if (checkPoint(point1))
			info.pointsOfIntersection.push_back(point1);

		if (checkPoint(point2))
			info.pointsOfIntersection.push_back(point2);
	}
	else if (discriminant == 0)
	{

		float x = ((-B) + sqrtf(discriminant)) / (2 * A);
		float y = l.GetY(x);

		Vector2D point = Vector2D(x,y);

		if (checkPoint(point))
		{
			info.pointsOfIntersection = { point };
		}

	}

	return info;
}

IntersectionInfo Engine::Maths::CheckIntersection(Rect& r, Circle& c)
{
	IntersectionInfo info = IntersectionInfo();
	std::vector<Line> lines = r.GetLines();

	for (auto line : lines)
	{
		info += CheckIntersection(line, c);
	}
	
	return info;
}

bool Engine::Maths::IsZero(float val)
{
	return val >= -WHSK_EPSILON && val <= WHSK_EPSILON;
}