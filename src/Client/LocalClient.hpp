#pragma once

#include "Client.hpp"
#include <Display.hpp>
#include <PlayerInput.hpp>
#include <memory>

class LocalClient : public Client
{
public:
    LocalClient(
        std::unique_ptr<Display> display,
        std::unique_ptr<PlayerInput> input
    );

    void connect(const GameConnection& connection) override;
    void start() override;
    void stop() override;
    void receive(const PlayerInputCommand& command) override;
    [[nodiscard]] PlayerStatus status() const override;
    void update(std::unique_ptr<GameplayUpdate> gameplayUpdate) override;

private:
    GameConnection gameConnection;
    std::unique_ptr<Display> gameDisplay;
    PlayerInputReceiver inputReceiver;
    std::unique_ptr<PlayerInput> playerInput;
};
