#pragma once

#include "RenderItem.hpp"
#include "RenderSceneBuilder.hpp"
#include <gmock/gmock.h>
#include <memory>

class MockRenderSceneBuilder : public RenderSceneBuilder
{
public:
    MOCK_METHOD(RenderItems, getRenderItems, (), (const, override));
};
