#pragma once

#include "ConnectedState.hpp"

namespace ue
{

class AbstractCallingState : public ConnectedState
{
private:
    void handleCallDrop() override;
    void handleCallRequest(common::PhoneNumber) override;

public:
    AbstractCallingState(Context& context);

};

}
