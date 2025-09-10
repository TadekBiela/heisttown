#pragma once

#include "Server.hpp"
#include <Client.hpp>
#include <memory>

class LocalServer : public Server
{
public:
    virtual ~LocalServer() = default;

    void start() override;
    void stop() override;
    void connect(std::shared_ptr<Client> client) override;
};
