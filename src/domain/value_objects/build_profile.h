#pragma once

#include <string>
#include <vector>

namespace offlinecode::domain {

enum class CppStandard { Cpp17, Cpp20, Cpp23 };
enum class Optimization { None, Size, Speed };

struct BuildProfile {
    std::string name{"Debug"};
    CppStandard standard{CppStandard::Cpp17};
    Optimization optimization{Optimization::None};
    bool debugSymbols{true};
    std::vector<std::string> warningFlags{"all", "extra"};
    std::vector<std::string> extraArguments;
};

} // namespace offlinecode::domain
