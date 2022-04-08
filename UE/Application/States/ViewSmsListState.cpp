#include "ViewSmsListState.hpp"
#include "ConnectedState.hpp"

namespace ue
{
ViewSmsListState::ViewSmsListState(Context &context)
    : ConnectedState(context)
{
    context.user.showSmsList(
                std::bind(&ViewSmsListState::onAcceptClicked, this),
                std::bind(&ViewSmsListState::onDeclineClicked, this)
                );
}

void ViewSmsListState::onAcceptClicked()
{

}

void ViewSmsListState::onDeclineClicked()
{
    context.setState<ConnectedState>();
}


}
