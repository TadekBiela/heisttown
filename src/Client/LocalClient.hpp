#ifndef LOCAL_CLIENT_HPP
#define LOCAL_CLIENT_HPP

#include "Client.hpp"
#include <GameDisplay.hpp>
#include <memory>

class LocalClient : public Client
{
public:
    LocalClient(std::unique_ptr<GameDisplay> display);
    virtual ~LocalClient() = default;

    void startSinglePlayerGame() override;

private:
    std::unique_ptr<GameDisplay> gameDisplay;
};

#endif // LOCAL_CLIENT_HPP
