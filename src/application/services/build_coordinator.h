#pragma once

#include "application/interfaces/compiler_service.h"

#include <memory>

namespace offlinecode::application {

class BuildCoordinator final : private IBuildObserver {
public:
    enum class State { Idle, Building, Cancelling };

    explicit BuildCoordinator(ICompilerService& compiler);

    [[nodiscard]] State state() const noexcept;
    [[nodiscard]] bool start(const BuildRequest& request, IBuildObserver& observer);
    [[nodiscard]] bool cancel();

private:
    void onOutput(std::string text) override;
    void onFinished(BuildResult result) override;

    ICompilerService& compiler_;
    IBuildObserver* observer_{nullptr};
    std::unique_ptr<IBuildHandle> handle_;
    State state_{State::Idle};
};

} // namespace offlinecode::application
