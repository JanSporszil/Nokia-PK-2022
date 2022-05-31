#include "ClosingState.hpp"
#include "UeGui/ITextMode.hpp"

ue::ClosingState::ClosingState(Context &context)
    : BaseState(context, "ClosingState")
{
    context.user.setCloseGuard([](){return false;});
    context.user.showAlertMode().setText("Closing...");
    using namespace std::chrono_literals;
    context.timer.startTimer(1s);
}

void ue::ClosingState::handleTimeout()
{
    exit(0);
}
