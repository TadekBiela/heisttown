#pragma once

#include "RenderItem.hpp"
#include <gmock/gmock.h>

class MockRenderItem : public RenderItem
{
public:
    MOCK_METHOD(void, render, (), (override));
};
