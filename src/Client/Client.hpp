#pragma once

#include <MainControlConnector.hpp>
#include <PlayerInput.hpp>

class Client : public MainControlConnector
{
public:
    virtual ~Client() = default;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void receive(const PlayerInputCommand& command) = 0;
};
