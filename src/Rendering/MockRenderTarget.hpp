#pragma once

#include "RenderItem.hpp"
#include "RenderTarget.hpp"
#include <gmock/gmock.h>
#include <memory>

class MockRenderTarget : public RenderTarget
{
public:
    MOCK_METHOD(void, render, (const RenderItems&), (const, override));
};
