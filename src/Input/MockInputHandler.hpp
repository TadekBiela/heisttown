#pragma once

#include "InputEvent.hpp"
#include "InputHandler.hpp"
#include <gmock/gmock.h>

class MockInputHandler : public InputHandler
{
public:
    MOCK_METHOD(bool, handle, (const InputEvent&), (override));
};
