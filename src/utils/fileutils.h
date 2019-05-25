#pragma once
#include <string>

namespace gengine {
    class FileUtils
    {
    public:
        static std::string read_file(const char* filepath);
    };
}