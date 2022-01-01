#pragma once
#define SP_PI 3.14159265358f

namespace gengine {
	namespace math {
		inline float toRadians(float degrees)
		{
			return degrees * (SP_PI / 180.0f);
		}
	}
}