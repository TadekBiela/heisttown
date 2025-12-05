#pragma once

#include "PlayerInput.hpp"
#include <gmock/gmock.h>

class MockPlayerInput : public PlayerInput
{
public:
    MOCK_METHOD(void, setInputReceiver, (PlayerInputReceiver), (override));
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, stop, (), (override));
    MOCK_METHOD(PlayerStatus, getPlayerStatus, (), (const, override));
};
