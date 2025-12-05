#pragma once

#include "RenderItem.hpp"
#include "RenderTarget.hpp"
#include <gmock/gmock.h>
#include <memory>

class MockRenderItem : public RenderItem
{
public:
    MOCK_METHOD(void, render, (), (override));
};
