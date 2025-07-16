#include "LocalServer.hpp"
#include <Client.hpp>
#include <MainControlConnector.hpp>
#include <memory>

void LocalServer::setMainControl(const MainControlConnection& controlConnection)
{
    (void)controlConnection;
}

void LocalServer::start()
{
}

void LocalServer::stop()
{
}

void LocalServer::connect(std::shared_ptr<Client> client)
{
    (void)client;
}
