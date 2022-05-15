#include "ConnectedState.hpp"
#include "AbstractCallingState.hpp"

namespace ue
{


AbstractCallingState::AbstractCallingState(Context &context)
    : ConnectedState(context)
{

}

void AbstractCallingState::handleCallDrop()
{
    context.setState<ConnectedState>();
}

void AbstractCallingState::handleCallRequest(common::PhoneNumber number)
{
    logger.logError("Received call request, but UE is already in call state");
}

}
