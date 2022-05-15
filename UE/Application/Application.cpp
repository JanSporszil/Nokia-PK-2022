#include "Application.hpp"
#include "States/NotConnectedState.hpp"

namespace ue
{

Application::Application(common::PhoneNumber phoneNumber,
                         common::ILogger &iLogger,
                         IBtsPort &bts,
                         IUserPort &user,
                         ITimerPort &timer)
    : context{iLogger, bts, user, timer},
      logger(iLogger, "[APP] ")
{
    logger.logInfo("Started");
    context.setState<NotConnectedState>();
}

Application::~Application()
{
    logger.logInfo("Stopped");
}

void Application::handleTimeout()
{
    context.state->handleTimeout();
}

void Application::handleSib(common::BtsId btsId)
{
    context.state->handleSib(btsId);
}

void Application::handleAttachAccept()
{
    context.state->handleAttachAccept();
}

void Application::handleAttachReject()
{
    context.state->handleAttachReject();
}

void Application::handleDisconnected()
{
    context.state->handleDisconnected();
}

void Application::handleSMSReceive(uint8_t mode, std::string content, common::PhoneNumber from, common::PhoneNumber to)
{
    context.state->handleSMSReceive(mode, content, from, to);
}

void Application::handleFailedSms()
{
    context.state->handleFailedSms();
}

void Application::handleCallDrop()
{
    context.state->handleCallDrop();
}

void Application::handleUnknownCallNumber()
{
    context.state->handleUnknownCallNumber();
}

void Application::handleCallAccepted()
{
    context.state->handleCallAccepted();
}

void Application::handleCallRequest(common::PhoneNumber number)
{
    context.state->handleCallRequest(number);
}

void Application::handleUnknownCallAccept()
{
    context.state->handleUnknownCallAccept();
}


}
