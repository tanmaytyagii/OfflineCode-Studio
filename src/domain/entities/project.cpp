#include "domain/entities/project.h"

#include <algorithm>
#include <utility>

namespace offlinecode::domain {

namespace {

std::size_t utf8ScalarCount(const std::string& text) {
    return static_cast<std::size_t>(std::count_if(text.begin(), text.end(), [](unsigned char byte) {
        return (byte & 0xC0U) != 0x80U;
    }));
}

} // namespace

Project::Project(std::string name, std::filesystem::path root)
    : name_(std::move(name)), root_(std::move(root)) {}

const std::string& Project::name() const noexcept {
    return name_;
}

const std::filesystem::path& Project::root() const noexcept {
    return root_;
}

const std::vector<std::filesystem::path>& Project::sources() const noexcept {
    return sources_;
}

const BuildProfile& Project::activeProfile() const noexcept {
    return activeProfile_;
}

std::vector<ProjectError> Project::validate() const {
    std::vector<ProjectError> errors;
    if (name_.empty()) {
        errors.push_back({ProjectErrorCode::EmptyName, "Project name cannot be empty."});
    } else if (utf8ScalarCount(name_) > MaxNameLength) {
        errors.push_back(
            {ProjectErrorCode::NameTooLong, "Project name cannot exceed 100 characters."});
    }

    if (root_.empty()) {
        errors.push_back({ProjectErrorCode::EmptyRoot, "Project root cannot be empty."});
    }

    for (const auto& source : sources_) {
        if (!isSafeRelativePath(source)) {
            errors.push_back({ProjectErrorCode::SourceOutsideRoot,
                              "Source paths must remain inside the project root."});
        }
    }
    return errors;
}

bool Project::addSource(const std::filesystem::path& relativePath, ProjectError* error) {
    const auto normalized = relativePath.lexically_normal();
    if (!isSafeRelativePath(normalized)) {
        if (error != nullptr) {
            *error = {ProjectErrorCode::SourceOutsideRoot,
                      "Source paths must remain inside the project root."};
        }
        return false;
    }

    if (std::find(sources_.begin(), sources_.end(), normalized) != sources_.end()) {
        if (error != nullptr) {
            *error = {ProjectErrorCode::DuplicateSource, "Source is already in the project."};
        }
        return false;
    }

    sources_.push_back(normalized);
    return true;
}

bool Project::removeSource(const std::filesystem::path& relativePath) {
    const auto normalized = relativePath.lexically_normal();
    const auto iterator = std::find(sources_.begin(), sources_.end(), normalized);
    if (iterator == sources_.end()) {
        return false;
    }
    sources_.erase(iterator);
    return true;
}

void Project::setActiveProfile(BuildProfile profile) {
    activeProfile_ = std::move(profile);
}

bool Project::isSafeRelativePath(const std::filesystem::path& path) {
    if (path.empty() || path.is_absolute() || path.has_root_path()) {
        return false;
    }

    const auto normalized = path.lexically_normal();
    const auto first = normalized.begin();
    return first != normalized.end() && *first != "..";
}

} // namespace offlinecode::domain
