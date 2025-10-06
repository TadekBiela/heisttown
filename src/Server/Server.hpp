#pragma once

#include <Client.hpp>
#include <memory>

class Server
{
public:
    virtual ~Server() = default;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void connect(std::shared_ptr<Client>) = 0;
    virtual void disconnect(std::shared_ptr<Client>) = 0;
};
