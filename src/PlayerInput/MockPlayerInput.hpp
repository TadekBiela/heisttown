#pragma once

#include "PlayerInput.hpp"
#include <gmock/gmock.h>

class MockPlayerInput : public PlayerInput
{
public:
    MOCK_METHOD(void, setInputReceiver, (PlayerInputReceiver));
    MOCK_METHOD(void, start, ());
    MOCK_METHOD(void, stop, ());
    MOCK_METHOD(PlayerStatus, getPlayerStatus, (), (const));
};
