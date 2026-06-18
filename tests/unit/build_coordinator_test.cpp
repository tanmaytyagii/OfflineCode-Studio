#include "application/services/build_coordinator.h"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "FAIL: " << message << '\n';
        std::exit(EXIT_FAILURE);
    }
}

class FakeHandle final : public offlinecode::application::IBuildHandle {
public:
    explicit FakeHandle(bool& cancelled) : cancelled_(cancelled) {}
    void cancel() override { cancelled_ = true; }

private:
    bool& cancelled_;
};

class FakeCompiler final : public offlinecode::application::ICompilerService {
public:
    std::unique_ptr<offlinecode::application::IBuildHandle>
    build(const offlinecode::application::BuildRequest&,
          offlinecode::application::IBuildObserver& observer) override {
        observer_ = &observer;
        return std::make_unique<FakeHandle>(cancelled);
    }

    void finish(offlinecode::application::BuildStatus status) {
        observer_->onFinished({status, "app", std::chrono::milliseconds(12), "done"});
        observer_ = nullptr;
    }

    bool cancelled{false};

private:
    offlinecode::application::IBuildObserver* observer_{nullptr};
};

class RecordingObserver final : public offlinecode::application::IBuildObserver {
public:
    void onOutput(std::string text) override { output += std::move(text); }
    void onFinished(offlinecode::application::BuildResult value) override {
        finished = true;
        result = std::move(value);
    }

    bool finished{false};
    std::string output;
    offlinecode::application::BuildResult result;
};

} // namespace

void runBuildCoordinatorTests() {
    FakeCompiler compiler;
    offlinecode::application::BuildCoordinator coordinator(compiler);
    RecordingObserver observer;
    offlinecode::application::BuildRequest request;
    request.sources = {"src/main.cpp"};
    request.outputArtifact = "build/app";

    require(coordinator.start(request, observer), "valid build should start");
    require(coordinator.state() == offlinecode::application::BuildCoordinator::State::Building,
            "coordinator should enter Building");
    require(!coordinator.start(request, observer), "overlapping build should be rejected");
    require(coordinator.cancel(), "active build should accept cancellation");
    require(compiler.cancelled, "cancellation should reach the build handle");
    compiler.finish(offlinecode::application::BuildStatus::Cancelled);
    require(observer.finished, "terminal result should reach the observer");
    require(coordinator.state() == offlinecode::application::BuildCoordinator::State::Idle,
            "coordinator should return to Idle");
}
