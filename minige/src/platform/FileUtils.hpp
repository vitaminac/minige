#pragma once
#include <string>

namespace gengine {
	namespace platform {
		class FileUtils
		{
		public:
			static std::string read_file(const char* filepath);
		};
	}
}