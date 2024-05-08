#include "LocalClient.hpp"

LocalClient::LocalClient(std::unique_ptr<GameDisplay> display)
    : gameDisplay(std::move(display))
{
}

void LocalClient::startSinglePlayerGame()
{
    gameDisplay->show();
}
