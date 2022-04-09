#pragma once

#include "ConnectedState.hpp"

namespace ue
{

class ViewingSmsState : public ConnectedState
{
protected:
    void onAcceptClicked() override;
    void onDeclineClicked() override;
public:
    ViewingSmsState(Context& context, int smsIndex);
};

}
