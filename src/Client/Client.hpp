#pragma once

#include <GameConnection.hpp>
#include <GameplayUpdate.hpp>
#include <InputPlayerHandler.hpp>

class Client
{
public:
    virtual ~Client() = default;

    virtual void connect(const GameConnection& connection) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void receive(const InputCommand& command) = 0;
    [[nodiscard]] virtual PlayerStatus status() const = 0;
    virtual void update(const GameplayUpdate&& gameplayUpdate) = 0;
};
