#include "fileutils.h"
#include <fstream>
#include <iostream>

namespace gengine {
    std::string gengine::FileUtils::read_file(const char* filepath)
    {
        FILE* file;
        fopen_s(&file, filepath, "r");
        fseek(file, 0, SEEK_END);
        unsigned long long length = ftell(file);
        char* content = new char[length + 1];
        memset(content, '\0', length + 1);
        fseek(file, 0, SEEK_SET);
        fread(content, sizeof(char), length, file);
        std::string shader(content);
        delete[] content;
        return shader;
    }
}