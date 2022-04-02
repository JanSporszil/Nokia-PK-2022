#include "ConnectedState.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
}

void ConnectedState::handleSMSReceive(uint8_t mode, std::string content)
{
    context.smsDB.addReceivedSms(content);
}

}
