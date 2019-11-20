#include "fileutils.h"
#include <fstream>
#include <iostream>

namespace gengine {
    std::string gengine::FileUtils::read_file(const char* filepath)
    {
        FILE* fp;
        if (fopen_s(&fp, filepath, "r") != 0) return "";

        fseek(fp, 0, SEEK_END);
        size_t length = ftell(fp);
        char* content = new char[length + 1];
        memset(content, '\0', length + 1);
        fseek(fp, 0, SEEK_SET);
        fread(content, sizeof(char), length, fp);
        std::string shader(content);
        delete[] content;
        return shader;
    }
}