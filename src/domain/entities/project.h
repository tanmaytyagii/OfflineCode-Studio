#pragma once

#include "domain/value_objects/build_profile.h"

#include <filesystem>
#include <string>
#include <vector>

namespace offlinecode::domain {

enum class ProjectErrorCode {
    EmptyName,
    NameTooLong,
    EmptyRoot,
    SourceOutsideRoot,
    DuplicateSource,
};

struct ProjectError {
    ProjectErrorCode code;
    std::string message;
};

class Project {
public:
    static constexpr std::size_t MaxNameLength = 100;

    Project(std::string name, std::filesystem::path root);

    [[nodiscard]] const std::string& name() const noexcept;
    [[nodiscard]] const std::filesystem::path& root() const noexcept;
    [[nodiscard]] const std::vector<std::filesystem::path>& sources() const noexcept;
    [[nodiscard]] const BuildProfile& activeProfile() const noexcept;

    [[nodiscard]] std::vector<ProjectError> validate() const;
    [[nodiscard]] bool addSource(const std::filesystem::path& relativePath,
                                 ProjectError* error = nullptr);
    [[nodiscard]] bool removeSource(const std::filesystem::path& relativePath);
    void setActiveProfile(BuildProfile profile);

private:
    [[nodiscard]] static bool isSafeRelativePath(const std::filesystem::path& path);

    std::string name_;
    std::filesystem::path root_;
    std::vector<std::filesystem::path> sources_;
    BuildProfile activeProfile_;
};

} // namespace offlinecode::domain
