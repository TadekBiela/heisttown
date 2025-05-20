#pragma once

#include "PlayerInput.hpp"
#include <gmock/gmock.h>

class MockPlayerInput : public PlayerInput
{
public:
    MOCK_METHOD1(setInputReceiver, void(PlayerInputReceiver));
    MOCK_METHOD0(start, void());
    MOCK_METHOD0(stop, void());
};
