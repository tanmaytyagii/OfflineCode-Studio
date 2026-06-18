#pragma once

#include "domain/value_objects/build_profile.h"

#include <chrono>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace offlinecode::application {

enum class BuildStatus { Succeeded, Failed, Cancelled };

struct BuildRequest {
    std::filesystem::path projectRoot;
    std::vector<std::filesystem::path> sources;
    std::filesystem::path outputArtifact;
    domain::BuildProfile profile;
};

struct BuildResult {
    BuildStatus status{BuildStatus::Failed};
    std::filesystem::path artifact;
    std::chrono::milliseconds duration{0};
    std::string rawOutput;
};

class IBuildObserver {
public:
    virtual ~IBuildObserver() = default;
    virtual void onOutput(std::string text) = 0;
    virtual void onFinished(BuildResult result) = 0;
};

class IBuildHandle {
public:
    virtual ~IBuildHandle() = default;
    virtual void cancel() = 0;
};

class ICompilerService {
public:
    virtual ~ICompilerService() = default;
    [[nodiscard]] virtual std::unique_ptr<IBuildHandle> build(const BuildRequest& request,
                                                              IBuildObserver& observer) = 0;
};

} // namespace offlinecode::application
