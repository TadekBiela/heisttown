#include "LocalClient.hpp"

LocalClient::LocalClient(std::unique_ptr<GameDisplay> display)
    : gameDisplay(std::move(display))
{
    gameDisplay->hide();
}

void LocalClient::run()
{
    gameDisplay->show();
}
