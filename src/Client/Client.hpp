#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <MainControlConnector.hpp>
#include <PlayerInput.hpp>

class Client : public MainControlConnector
{
public:
    virtual ~Client() = default;

    virtual void startSinglePlayerGame() = 0;
    virtual void receive(const PlayerInputCommand& command) = 0;
};

#endif // CLIENT_HPP
