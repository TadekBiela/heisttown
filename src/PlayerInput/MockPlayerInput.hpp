#ifndef MOCK_PLAYER_INPUT_HPP
#define MOCK_PLAYER_INPUT_HPP

#include "PlayerInput.hpp"
#include <gmock/gmock.h>

class MockPlayerInput : public PlayerInput
{
public:
    MOCK_METHOD1(setInputReceiver, void(PlayerInputReceiver));
    MOCK_METHOD0(start, void());
    MOCK_METHOD0(stop, void());
};

#endif // MOCK_PLAYER_INPUT_HPP
