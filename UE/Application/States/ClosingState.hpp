#pragma once
#include "BaseState.hpp"
namespace ue
{
class ClosingState : public BaseState
{
    // ITimerEventsHandler interface
public:
    ClosingState(Context &context);
    void handleTimeout() override;
};

}
