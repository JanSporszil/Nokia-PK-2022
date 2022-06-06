#include "BaseState.hpp"

namespace ue
{

BaseState::BaseState(Context &context, const std::string &name)
    : context(context),
      logger(context.logger, "[" + name + "]")
{
    logger.logDebug("entry");
    context.user.setCloseGuard( [](){return true;});
}

BaseState::~BaseState()
{
    logger.logDebug("exit");
}

void BaseState::handleTimeout()
{
    logger.logError("Uexpected: handleTimeout");
}

void BaseState::handleSib(common::BtsId btsId)
{
    logger.logError("Uexpected: handleSib: ", btsId);
}

void BaseState::handleAttachAccept()
{
    logger.logError("Uexpected: handleTimeout");
}

void BaseState::handleAttachReject()
{
    logger.logError("Uexpected: handleAttachReject");
}

void BaseState::handleDisconnected()
{
    logger.logError("Uexpected: handleDisconnected");
}

void BaseState::handleSMSReceive(const std::string &content, common::PhoneNumber from, common::PhoneNumber to)
{
    logger.logError("Unexpected: handleSMSReceive");
}

void BaseState::handleFailedSms()
{
    logger.logError("Unexpected: handleFailedSms");
}

void BaseState::handleCallDrop()
{
    logger.logError("Unexpected: handleCallDrop");
}

void BaseState::handleUnknownCallNumber()
{
    logger.logError("Unexpected: handleUnknownCallNumber");
}

void BaseState::handleCallAccepted()
{
    logger.logError("Unexpected: handleCallAccepted");
}

void BaseState::handleCallRequest(common::PhoneNumber number)
{
    logger.logError("Unexpected: handleCallRequest");
}

void BaseState::handleUnknownCallAccept()
{
    logger.logError("Unexpected: handleUnknownCallAccept");
}

void BaseState::handleCallTalkReceive(const std::string &, common::PhoneNumber)
{
    logger.logError("Unexpected: handleCallTalkReceive");
}

}
