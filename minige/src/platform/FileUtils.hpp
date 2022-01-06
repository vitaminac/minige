#pragma once
#include "so.h"
#include <string>

namespace gengine {
	namespace platform {
		class SO_API FileUtils
		{
		public:
			static std::string read_file(const char* filepath);
		};
	}
}