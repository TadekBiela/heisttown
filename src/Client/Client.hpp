#pragma once

#include <PlayerInput.hpp>
#include <functional>

enum class GameCommand
{
    Pause = 0,
    NoCommand = 1
};

using GameConnection = std::function<void(const GameCommand&)>;


class Client
{
public:
    virtual ~Client() = default;

    virtual void connect(const GameConnection& connection) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void receive(const PlayerInputCommand& command) = 0;
};
