#pragma once

#include <Client.hpp>
#include <GameSession.hpp>
#include <memory>

class Server
{
public:
    virtual ~Server() = default;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual PlayerID connect(const std::shared_ptr<Client>&) = 0;
    virtual void disconnect(const PlayerID&) = 0;
};
