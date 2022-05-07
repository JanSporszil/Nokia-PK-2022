#pragma once

#include "ConnectedState.hpp"

namespace ue
{

class AbstractCallingState : public ConnectedState
{
private:
    void handleCallDrop() override;
public:
    AbstractCallingState(Context& context);

};

}
