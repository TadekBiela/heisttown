#pragma once

#include "InputDispatcher.hpp"
#include "InputHandler.hpp"
#include <gmock/gmock.h>
#include <memory>

class MockInputDispatcher : public InputDispatcher
{
public:
    MockInputDispatcher()
        : InputDispatcher(nullptr)
    {}

    MOCK_METHOD(void, addHandler, (const std::shared_ptr<InputHandler>&), (override));
    MOCK_METHOD(void, dispatch, (), (override));
};
