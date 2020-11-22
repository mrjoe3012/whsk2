#pragma once

namespace Engine
{

	namespace Maths
	{

		class Vector
		{

		public:
			Vector() {};
			~Vector() {};

			virtual float Magnitude() const = 0;
			virtual float SquareMagnitude() const = 0;

		};

	}

}