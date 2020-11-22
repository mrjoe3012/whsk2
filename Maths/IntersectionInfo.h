#pragma once
#include "Vector2D.h"
#include <vector>

namespace Engine
{
	namespace Maths
	{
		// Holds information about the intersection of two objects.
		struct IntersectionInfo
		{

		public:
			IntersectionInfo();
			IntersectionInfo(const IntersectionInfo&);
			~IntersectionInfo();

			std::vector<Vector2D> pointsOfIntersection = std::vector<Vector2D>(); // An array of length pointCount containing each point of contact.
			bool identical = false; // Were the two shapes compared identical?

			IntersectionInfo operator+(IntersectionInfo& rhs);
			void operator+=(const IntersectionInfo& rhs);
			void operator=(const IntersectionInfo& rhs);

		};
	}
}