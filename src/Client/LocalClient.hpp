#pragma once

#include "Client.hpp"
#include <GameConnection.hpp>
#include <GameplayUpdate.hpp>
#include <Scene.hpp>
#include <Input.hpp>
#include <memory>

class LocalClient : public Client
{
public:
    LocalClient(
        std::shared_ptr<Scene> scene,
        std::unique_ptr<Input> input
    );

    void connect(const GameConnection& connection) override;
    void start() override;
    void stop() override;
    void receive(const InputCommand& command) override;
    [[nodiscard]] PlayerStatus status() const override;
    void update(const GameplayUpdate&& gameplayUpdate) override;

private:
    GameConnection gameConnection;
    std::shared_ptr<Scene> gameScene;
    InputReceiver inputReceiver;
    std::unique_ptr<Input> playerInput;
};
