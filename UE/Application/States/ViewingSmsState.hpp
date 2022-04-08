#pragma once

#include "ConnectedState.hpp"

namespace ue
{

class ViewingSmsState : public ConnectedState
{
protected:
    void onAcceptClicked();
    void onDeclineClicked();
public:
    ViewingSmsState(Context& context, int smsIndex);
};

}
