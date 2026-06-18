#include "domain/entities/project.h"

#include <cstdlib>
#include <filesystem>
#include <iostream>

void runBuildCoordinatorTests();

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "FAIL: " << message << '\n';
        std::exit(EXIT_FAILURE);
    }
}

void projectRejectsUnsafeSources() {
    offlinecode::domain::Project project("sample", std::filesystem::path("/tmp/sample"));
    offlinecode::domain::ProjectError error{};

    require(project.addSource("src/main.cpp", &error), "safe relative source should be added");
    require(!project.addSource("../secret.cpp", &error), "parent traversal should be rejected");
    require(error.code == offlinecode::domain::ProjectErrorCode::SourceOutsideRoot,
            "traversal should produce SourceOutsideRoot");
    require(!project.addSource("src/main.cpp", &error), "duplicate source should be rejected");
    require(project.sources().size() == 1, "only one valid source should remain");
}

void projectValidatesRequiredFields() {
    offlinecode::domain::Project project("", {});
    const auto errors = project.validate();
    require(errors.size() == 2, "empty project should report name and root errors");
}

void projectNameLimitCountsUtf8Scalars() {
    std::string name;
    for (std::size_t index = 0; index < offlinecode::domain::Project::MaxNameLength; ++index) {
        name += "\xC3\xA9";
    }

    offlinecode::domain::Project validProject(name, "/tmp/sample");
    require(validProject.validate().empty(), "100 UTF-8 scalars should satisfy the name limit");
    name += "x";
    offlinecode::domain::Project longProject(name, "/tmp/sample");
    require(longProject.validate().size() == 1, "101 UTF-8 scalars should exceed the name limit");
}

} // namespace

int main() {
    projectRejectsUnsafeSources();
    projectValidatesRequiredFields();
    projectNameLimitCountsUtf8Scalars();
    runBuildCoordinatorTests();
    std::cout << "All offlinecode core tests passed.\n";
    return EXIT_SUCCESS;
}
