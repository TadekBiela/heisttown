#ifndef SERVER_HPP
#define SERVER_HPP

#include <Client.hpp>
#include <MainControlConnector.hpp>
#include <memory>

class Server : public MainControlConnector
{
public:
    virtual ~Server() = default;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void connect(std::shared_ptr<Client>) = 0;
};

#endif // SERVER_HPP
