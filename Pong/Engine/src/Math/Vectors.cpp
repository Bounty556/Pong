#include "Vectors.h"

#include <Math/Functions.h>
#include <Math/Constants.h>

#include <Core/Logger.h>

namespace Soul
{
	namespace Math
	{
		f32 Distance(const sf::Vector2f& a, const sf::Vector2f& b)
		{
			sf::Vector2f line = a - b;
			return Magnitude(line);
		}

		f32 Magnitude(const sf::Vector2f& a)
		{
			return Math::Sqrt(a.x * a.x + a.y * a.y);
		}

		sf::Vector2f Normalize(const sf::Vector2f& a)
		{
			f32 mag = Magnitude(a);
			if (mag == 0.0f)
				return sf::Vector2f(1.0f, 0.0f); // TODO: Change?
			return a / Magnitude(a);
		}

		sf::Vector2f Normal(const sf::Vector2f& a)
		{
			return sf::Vector2f(-a.y, a.x);
		}

		sf::Vector2f AngleToVector(f32 degrees)
		{
			f32 rad = ToRadians(degrees);
			return sf::Vector2f((f32)Math::Cos(rad), (f32)Math::Sin(rad));
		}

		f32 VectorToAngle(const sf::Vector2f& v)
		{
			f32 theta = ToDegrees(Atan2(-v.y, v.x));

			return theta;
		}
	}
}