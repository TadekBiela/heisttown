#include "LocalClient.hpp"
#include <iostream>

LocalClient::LocalClient(
    std::unique_ptr<GameDisplay> display,
    std::unique_ptr<PlayerInput> input
)
    : gameDisplay(std::move(display))
    , playerInput(std::move(input))
{
    inputReceiver = [&](const PlayerInputCommand& command)
    {
        this->receive(command);
    };
    playerInput->setInputReceiver(inputReceiver);
}

void LocalClient::startSinglePlayerGame()
{
    gameDisplay->show();
    playerInput->start();
}

void LocalClient::receive(const PlayerInputCommand& command)
{
    std::cerr << "LocalClient: " << command << std::endl;
    playerInput->stop();
}
