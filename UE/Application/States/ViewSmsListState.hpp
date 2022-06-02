#pragma once

#include "ConnectedState.hpp"

namespace ue
{

class ViewSmsListState : public ConnectedState
{
protected:
    void onAcceptClicked() override;
    void onDeclineClicked() override;
    void handleSMSReceive(const std::string &content, common::PhoneNumber from, common::PhoneNumber to);
public:
    ViewSmsListState(Context& context);
};

}
