#include "LocalClient.hpp"
#include <iostream>
#include <utility>

LocalClient::LocalClient(
    std::unique_ptr<PlayerInput> input
)
    : gameConnection([](const GameCommand&) {})
    , playerInput(std::move(input))
{
    inputReceiver = [&](const PlayerInputCommand& command)
    {
        this->receive(command);
    };
    playerInput->setInputReceiver(inputReceiver);
}

void LocalClient::connect(const GameConnection& connection)
{
    gameConnection = connection;
}

void LocalClient::start()
{
    playerInput->start();
}

void LocalClient::stop()
{
    playerInput->stop();
}

void LocalClient::receive(const PlayerInputCommand& command)
{
    std::cerr << "LocalClient: " << command << "\n";
    if (command == "Keyboard: ESC")
    {
        stop();
        gameConnection(GameCommand::Pause);
    }
}

PlayerStatus LocalClient::status() const
{
    return playerInput->getPlayerStatus();
}

void LocalClient::update(std::unique_ptr<GameplayUpdate> gameplayUpdate)
{
    gameplayUpdate.get();
}
