#include "LocalClient.hpp"
#include <iostream>

LocalClient::LocalClient(
    std::shared_ptr<Scene> scene,
    std::unique_ptr<Input> input
)
    : gameConnection([](const GameCommand&) {})
    , gameScene(std::move(scene))
    , playerInput(std::move(input))
{
    inputReceiver = [&](const InputCommand& command)
    {
        this->receive(command);
    };

    if (playerInput)
    {
        playerInput->setInputReceiver(inputReceiver);
    }
}

void LocalClient::connect(const GameConnection& connection)
{
    gameConnection = connection;
}

void LocalClient::start()
{
    if (playerInput)
    {
        playerInput->start();
    }
    gameScene->show();
}

void LocalClient::stop()
{
    if (playerInput)
    {
        playerInput->stop();
    }
    gameScene->hide();
}

void LocalClient::receive(const InputCommand& command)
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
    // return playerInput->getPlayerStatus();
    return PlayerStatus {};
}

void LocalClient::update(const GameplayUpdate&& gameplayUpdate)
{
    gameScene->update(gameplayUpdate.gameSceneUpdate);
}
