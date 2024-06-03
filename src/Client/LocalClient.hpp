#ifndef LOCAL_CLIENT_HPP
#define LOCAL_CLIENT_HPP

#include "Client.hpp"
#include <GameDisplay.hpp>
#include <PlayerInput.hpp>
#include <memory>

class LocalClient : public Client
{
public:
    LocalClient(
        std::unique_ptr<GameDisplay> display,
        std::unique_ptr<PlayerInput> input);
    virtual ~LocalClient() = default;

    void startSinglePlayerGame() override;
    void receive(const PlayerInputCommand& command) override;

private:
    std::unique_ptr<GameDisplay> gameDisplay;
    PlayerInputReceiver inputReceiver;
    std::unique_ptr<PlayerInput> playerInput;
};

#endif // LOCAL_CLIENT_HPP
