#ifndef PLAYER_INPUT_HPP
#define PLAYER_INPUT_HPP

#include <functional>
#include <string>

using PlayerInputCommand = std::string;
using PlayerInputReceiver = std::function<void(const PlayerInputCommand&)>;

class PlayerInput
{
public:
    virtual ~PlayerInput() = default;

    virtual void setInputReceiver(PlayerInputReceiver inputReceiver) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
};

#endif // PLAYER_INPUT_HPP
