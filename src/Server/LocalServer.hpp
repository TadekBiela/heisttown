#pragma once

#include "Server.hpp"
#include <Client.hpp>
#include <MainControlConnector.hpp>
#include <memory>

class LocalServer : public Server
{
public:
    virtual ~LocalServer() = default;

    void setMainControl(const MainControlConnection& controlConnection) override;
    void start() override;
    void stop() override;
    void connect(std::shared_ptr<Client> client) override;
};
