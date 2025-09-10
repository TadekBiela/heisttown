#pragma once

#include "Client.hpp"
#include <GameDisplay.hpp>
#include <PlayerInput.hpp>
#include <memory>

class LocalClient : public Client
{
public:
    LocalClient(
        std::unique_ptr<GameDisplay> display,
        std::unique_ptr<PlayerInput> input);

    void connect(const GameConnection& connection) override;
    void start() override;
    void stop() override;
    void receive(const PlayerInputCommand& command) override;

private:
    GameConnection gameConnection;
    std::unique_ptr<GameDisplay> gameDisplay;
    PlayerInputReceiver inputReceiver;
    std::unique_ptr<PlayerInput> playerInput;
};
