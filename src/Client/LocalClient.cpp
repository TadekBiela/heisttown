#include "LocalClient.hpp"
#include <iostream>

LocalClient::LocalClient(
    std::unique_ptr<GameDisplay> display,
    std::unique_ptr<PlayerInput> input
)
    : mainControlConnection([](const MainCommand&) {})
    , gameDisplay(std::move(display))
    , playerInput(std::move(input))
{
    inputReceiver = [&](const PlayerInputCommand& command)
    {
        this->receive(command);
    };
    playerInput->setInputReceiver(inputReceiver);
}

void LocalClient::setMainControl(const MainControlConnection& controlConnection)
{
    mainControlConnection = controlConnection;
}

void LocalClient::start()
{
    gameDisplay->show();
    playerInput->start();
}

void LocalClient::stop()
{
    gameDisplay->hide();
    playerInput->stop();
}

void LocalClient::receive(const PlayerInputCommand& command)
{
    std::cerr << "LocalClient: " << command << std::endl;
    if (command == "Keyboard: ESC")
    {
        stop();
        mainControlConnection("SinglePlayer->Pause");
    }
}
