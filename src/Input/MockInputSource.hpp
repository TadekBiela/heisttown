#pragma once

#include "InputEvent.hpp"
#include "InputSource.hpp"
#include <gmock/gmock.h>
#include <vector>

class MockInputSource : public InputSource
{
public:
    MOCK_METHOD(std::vector<InputEvent>, pollEvents, (), (override));
};
