#pragma once

#include "ConnectedState.hpp"

namespace ue
{

class ViewSmsListState : public ConnectedState
{
protected:
    void onAcceptClicked() override;
    void onDeclineClicked() override;
public:
    ViewSmsListState(Context& context);
};

}
