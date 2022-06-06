#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Application.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/IBtsPortMock.hpp"
#include "Mocks/IUserPortMock.hpp"
#include "Mocks/ITimerPortMock.hpp"
#include "Mocks/IUeGuiMock.hpp"
#include "Mocks/SmsMock.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Ports/UserPort.hpp"
#include "States/ConnectedState.hpp"
#include "States/SendingSmsState.hpp"
#include "States/ViewSmsListState.hpp"
#include "States/DialingNumberState.hpp"
#include "IUeGui.hpp"
#include "UeGui/ITextMode.hpp"
#include <memory>

namespace ue
{
using namespace ::testing;

class ApplicationTestSuite : public Test
{
protected:
    const common::PhoneNumber PHONE_NUMBER{112};
    const common::BtsId BTS_ID{42};
    NiceMock<common::ILoggerMock> loggerMock;
    NiceMock<IBtsPortMock> btsPortMock;
    NiceMock<IUserPortMock> userPortMock;
    NiceMock<ITimerPortMock> timerPortMock;
    NiceMock<ITextModeMock> textModeMock;
    NiceMock<IDialModeMock> dialModeMock;
    NiceMock<ICallModeMock> callModeMock;
    NiceMock<ISmsComposeModeMock> smsComposeModeMock;
    NiceMock<IListViewModeMock> listViewModeMock;
    NiceMock<SmsDBMock> smsDbMock;

    Expectation expectNotConnected = EXPECT_CALL(userPortMock, showNotConnected());

    Application objectUnderTest{PHONE_NUMBER,
                                loggerMock,
                                btsPortMock,
                                userPortMock,
                                timerPortMock};

    Context& getPrivateContext()
    {
        return objectUnderTest.context;
    }

    void clickAcceptButton()
    {
        dynamic_cast<ConnectedState*>(getPrivateContext().state.get())->onAcceptClicked();
    }

    void clickRejectButton()
    {
        dynamic_cast<ConnectedState*>(getPrivateContext().state.get())->onDeclineClicked();
    }
};

struct ApplicationNotConnectedTestSuite : ApplicationTestSuite
{
    void goIntoConnectingState();
};

struct ApplicationConnectingTestSuite : ApplicationNotConnectedTestSuite
{
    ApplicationConnectingTestSuite();
    void goIntoConnectedState();
};

struct ApplicationConnectedTestSuite : ApplicationConnectingTestSuite
{
    ApplicationConnectedTestSuite();
    void goIntoSendingSmsState();
    void goIntoViewingSmsListState();
    void goIntoDialingNumberState();
    void goIntoReceivingCallState();
};

struct ApplicationSendingSmsTestSuite : ApplicationConnectedTestSuite
{
    ApplicationSendingSmsTestSuite();
};

struct ApplicationViewingSmsListTestSuite : ApplicationConnectedTestSuite
{
    ApplicationViewingSmsListTestSuite();
    void goIntoViewingSmsState();
};

struct ApplicationDialingNumberTestSuite : ApplicationConnectedTestSuite
{
    ApplicationDialingNumberTestSuite();
    void goIntoMakingCallState();
};

struct ApplicationReceivingCallTestSuite : ApplicationConnectedTestSuite
{
    ApplicationReceivingCallTestSuite();
};

struct ApplicationViewingSmsTestSuite : ApplicationViewingSmsListTestSuite
{
    ApplicationViewingSmsTestSuite();
};

struct ApplicationMakingCallTestSuite : ApplicationDialingNumberTestSuite
{
    ApplicationMakingCallTestSuite();
    void goIntoTalkingState();
};

struct ApplicationTalkingTestSuite : ApplicationMakingCallTestSuite
{
    ApplicationTalkingTestSuite();
};


ApplicationConnectingTestSuite::ApplicationConnectingTestSuite()
{
    goIntoConnectingState();
}

ApplicationSendingSmsTestSuite::ApplicationSendingSmsTestSuite()
{
    goIntoSendingSmsState();
}

void ApplicationNotConnectedTestSuite::goIntoConnectingState()
{
    EXPECT_CALL(btsPortMock, sendAttachRequest(BTS_ID));
    EXPECT_CALL(timerPortMock, startTimer(_));
    EXPECT_CALL(userPortMock, showConnecting());
    objectUnderTest.handleSib(BTS_ID);
}

ApplicationConnectedTestSuite::ApplicationConnectedTestSuite()
{
    goIntoConnectedState();
}

ApplicationViewingSmsListTestSuite::ApplicationViewingSmsListTestSuite()
{
    goIntoViewingSmsListState();
}

void ApplicationViewingSmsListTestSuite::goIntoViewingSmsState()
{
    EXPECT_CALL(userPortMock, showSmsList());
    EXPECT_CALL(userPortMock, getCurrentMenuIndex()).WillOnce(Return(0));
    EXPECT_CALL(userPortMock, showSms(_));
    EXPECT_CALL(userPortMock, getSmsDB()).WillOnce(ReturnRef(smsDbMock));
    objectUnderTest.handleSMSReceive("dummy", PHONE_NUMBER, PHONE_NUMBER);
    clickAcceptButton();
}

void ApplicationConnectedTestSuite::goIntoSendingSmsState()
{
    EXPECT_CALL(userPortMock, getCurrentMenuIndex).WillOnce(Return(UserPort::MenuList::COMPOSE_SMS));
    EXPECT_CALL(userPortMock, showComposeSms).WillOnce(ReturnRef(smsComposeModeMock));
    clickAcceptButton();
}

void ApplicationConnectedTestSuite::goIntoViewingSmsListState()
{
    EXPECT_CALL(userPortMock, getCurrentMenuIndex).WillOnce(Return(UserPort::MenuList::VIEW_SMS));
    EXPECT_CALL(userPortMock, showSmsList);
    clickAcceptButton();
}

void ApplicationConnectedTestSuite::goIntoDialingNumberState()
{
    EXPECT_CALL(userPortMock, getCurrentMenuIndex).WillOnce(Return(UserPort::MenuList::CALL));
    EXPECT_CALL(userPortMock, showDialMode).WillOnce(ReturnRef(dialModeMock));
    clickAcceptButton();
}

void ApplicationConnectedTestSuite::goIntoReceivingCallState()
{
    EXPECT_CALL(userPortMock, showAlertMode()).WillRepeatedly(ReturnRef(textModeMock));
    EXPECT_CALL(timerPortMock, startTimer(_));
    objectUnderTest.handleCallRequest(PHONE_NUMBER);
}

void ApplicationConnectingTestSuite::goIntoConnectedState()
{
    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(userPortMock, showConnected()).Times(AnyNumber());
    objectUnderTest.handleAttachAccept();
}

ApplicationDialingNumberTestSuite::ApplicationDialingNumberTestSuite()
{
    goIntoDialingNumberState();
}

void ApplicationDialingNumberTestSuite::goIntoMakingCallState()
{
    EXPECT_CALL(userPortMock, showAlertMode()).WillOnce(ReturnRef(textModeMock));
    EXPECT_CALL(timerPortMock, startTimer(_));
    clickAcceptButton();
}

ApplicationViewingSmsTestSuite::ApplicationViewingSmsTestSuite()
{
    goIntoViewingSmsState();
}

ApplicationMakingCallTestSuite::ApplicationMakingCallTestSuite()
{
    goIntoMakingCallState();
}

void ApplicationMakingCallTestSuite::goIntoTalkingState()
{
    EXPECT_CALL(timerPortMock, stopTimer()).Times(2);
    EXPECT_CALL(userPortMock, showCallMode()).WillOnce(ReturnRef(callModeMock));
    EXPECT_CALL(timerPortMock, startTimer(_));
    objectUnderTest.handleCallAccepted();
}

ApplicationReceivingCallTestSuite::ApplicationReceivingCallTestSuite()
{
    goIntoReceivingCallState();
}

ApplicationTalkingTestSuite::ApplicationTalkingTestSuite()
{
    goIntoTalkingState();
}

TEST_F(ApplicationNotConnectedTestSuite, shallRequestAttachOnSib)
{
    goIntoConnectingState();
}

TEST_F(ApplicationConnectingTestSuite, shallCompleteAttachWhenAttachAccepted)
{
    goIntoConnectedState();
}

TEST_F(ApplicationConnectingTestSuite, shallFailAttachWhenAttachRejected)
{
    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(userPortMock, showNotConnected());
    objectUnderTest.handleAttachReject();
}

TEST_F(ApplicationConnectingTestSuite, shallFailAttachOnTimeout)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    objectUnderTest.handleTimeout();
}


TEST_F(ApplicationConnectedTestSuite, shallHandleDisconnected)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    objectUnderTest.handleDisconnected();
}

TEST_F(ApplicationConnectedTestSuite, shallEnterReceivingCallState)
{
    goIntoReceivingCallState();
}

TEST_F(ApplicationConnectedTestSuite, shallEnterViewingSmsListState)
{
    goIntoViewingSmsListState();
}

TEST_F(ApplicationConnectedTestSuite, shallEnterSendingSmsState)
{
    goIntoSendingSmsState();
}

TEST_F(ApplicationConnectedTestSuite, shallEnterDialingNumberState)
{
    goIntoDialingNumberState();
}

TEST_F(ApplicationSendingSmsTestSuite, shallSendSms)
{
    EXPECT_CALL(btsPortMock, sendSms(_, _));
    EXPECT_CALL(userPortMock, getSmsDB()).WillOnce(ReturnRef(smsDbMock));
    clickAcceptButton();
}

TEST_F(ApplicationSendingSmsTestSuite, shallBackToMenuOnReject)
{
    EXPECT_CALL(userPortMock, showConnected());
    clickRejectButton();
}

TEST_F(ApplicationViewingSmsListTestSuite, shallViewSmsOnAccept)
{
    goIntoViewingSmsState();
}

TEST_F(ApplicationViewingSmsTestSuite, shallBackToSmsListOnReject)
{
    EXPECT_CALL(userPortMock, showSmsList());
    clickRejectButton();
}

TEST_F(ApplicationDialingNumberTestSuite, shallGoIntoMakingCallOnAccpet)
{
    goIntoMakingCallState();
}

TEST_F(ApplicationDialingNumberTestSuite, shallBackToMainMenuOnReject)
{
    EXPECT_CALL(userPortMock, showConnected());
    clickRejectButton();
}

TEST_F(ApplicationMakingCallTestSuite, shallGoToTalkingStateOnCallAccpeted)
{
    goIntoTalkingState();
}

TEST_F(ApplicationMakingCallTestSuite, shallGoToMainMenuOnTimeout)
{
    EXPECT_CALL(userPortMock, showConnected());
    objectUnderTest.handleTimeout();
}

TEST_F(ApplicationMakingCallTestSuite, shallBackToMainMenuOnReject)
{
    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(btsPortMock, sendDropCall(_));
    EXPECT_CALL(userPortMock, showConnected());
    clickRejectButton();
}

TEST_F(ApplicationMakingCallTestSuite, shallBackToMainMenuOnCallDrop)
{
    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(userPortMock, showConnected());
    objectUnderTest.handleCallDrop();
}

TEST_F(ApplicationTalkingTestSuite, shallBackToMainMenuOnReject)
{
    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(btsPortMock, sendDropCall(_));
    EXPECT_CALL(userPortMock, showConnected());
    clickRejectButton();
}

TEST_F(ApplicationTalkingTestSuite, shallBackToMainMenuOnTimeout)
{
    EXPECT_CALL(btsPortMock, sendDropCall(_));
    EXPECT_CALL(userPortMock, showConnected());
    objectUnderTest.handleTimeout();
}

TEST_F(ApplicationTalkingTestSuite, shallGoToMainMenuOnCallDrop)
{
    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(userPortMock, showConnected());
    objectUnderTest.handleCallDrop();
}

TEST_F(ApplicationTalkingTestSuite, shallSendTalkOnAccept)
{
    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(btsPortMock, sendCallTalk(_, _));
    EXPECT_CALL(timerPortMock, startTimer(_));
    clickAcceptButton();
}

TEST_F(ApplicationTalkingTestSuite, shallAddLineOnNewMessage)
{
    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(callModeMock, appendIncomingText(_));
    EXPECT_CALL(timerPortMock, startTimer(_));
    objectUnderTest.handleCallTalkReceive("Test", PHONE_NUMBER);
}

TEST_F(ApplicationReceivingCallTestSuite, shallGoToMainMenuOnReject)
{
    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(btsPortMock, sendDropCall(_));
    EXPECT_CALL(userPortMock, showConnected());
    clickRejectButton();
}

TEST_F(ApplicationReceivingCallTestSuite, shallGoToMainMenuOnTimeout)
{
    EXPECT_CALL(btsPortMock, sendDropCall(_));
    EXPECT_CALL(userPortMock, showConnected());
    objectUnderTest.handleTimeout();
}

TEST_F(ApplicationReceivingCallTestSuite, shallGoToMainMenuOnCallDrop)
{
    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(userPortMock, showConnected());
    objectUnderTest.handleCallDrop();
}

TEST_F(ApplicationReceivingCallTestSuite, shallGoToTalkingStateOnAccept)
{
    EXPECT_CALL(timerPortMock, stopTimer()).Times(2);
    EXPECT_CALL(userPortMock, showCallMode()).WillOnce(ReturnRef(callModeMock));
    EXPECT_CALL(timerPortMock, startTimer(_));
    EXPECT_CALL(btsPortMock, sendCallAccepted(_));
    clickAcceptButton();
}

}
