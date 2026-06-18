#include "application/services/build_coordinator.h"

#include <utility>

namespace offlinecode::application {

BuildCoordinator::BuildCoordinator(ICompilerService& compiler) : compiler_(compiler) {}

BuildCoordinator::State BuildCoordinator::state() const noexcept {
    return state_;
}

bool BuildCoordinator::start(const BuildRequest& request, IBuildObserver& observer) {
    if (state_ != State::Idle || request.sources.empty() || request.outputArtifact.empty()) {
        return false;
    }

    observer_ = &observer;
    state_ = State::Building;
    auto handle = compiler_.build(request, *this);
    if (state_ == State::Idle) {
        return true;
    }
    if (handle == nullptr) {
        state_ = State::Idle;
        observer_ = nullptr;
        return false;
    }
    handle_ = std::move(handle);
    return true;
}

bool BuildCoordinator::cancel() {
    if (state_ != State::Building || handle_ == nullptr) {
        return false;
    }
    state_ = State::Cancelling;
    handle_->cancel();
    return true;
}

void BuildCoordinator::onOutput(std::string text) {
    if (observer_ != nullptr) {
        observer_->onOutput(std::move(text));
    }
}

void BuildCoordinator::onFinished(BuildResult result) {
    auto* observer = observer_;
    handle_.reset();
    observer_ = nullptr;
    state_ = State::Idle;
    if (observer != nullptr) {
        observer->onFinished(std::move(result));
    }
}

} // namespace offlinecode::application
