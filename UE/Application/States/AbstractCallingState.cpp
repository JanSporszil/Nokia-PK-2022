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

}
