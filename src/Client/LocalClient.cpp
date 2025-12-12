#include "LocalClient.hpp"
#include <iostream>

LocalClient::LocalClient(
    std::shared_ptr<Scene> scene,
    const std::shared_ptr<InputDispatcher>& inputDispatcher
)
    : gameConnection([](const GameCommand&) {})
    , gameScene(std::move(scene))
    , playerInput(std::make_shared<InputPlayerHandler>())
{
    inputReceiver = [&](const InputCommand& command)
    {
        this->receive(command);
    };

    playerInput->setInputReceiver(inputReceiver);
    inputDispatcher->addHandler(playerInput);
}

void LocalClient::connect(const GameConnection& connection)
{
    gameConnection = connection;
}

void LocalClient::start()
{
    gameScene->show();
}

void LocalClient::stop()
{
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
    return playerInput->getPlayerStatus();
}

void LocalClient::update(const GameplayUpdate&& gameplayUpdate)
{
    gameScene->update(gameplayUpdate.gameSceneUpdate);
}
