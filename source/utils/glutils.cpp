
#include "utils/glutils.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace GLUtils {
    std::string loadShaderSource(std::string fileName)
    {
        std::ifstream fileSource(fileName);
        if (!fileSource.is_open()) {
            return "";
        }
        auto ss = std::ostringstream{};
        ss << fileSource.rdbuf();
        fileSource.close();
        return ss.str();
    }
}