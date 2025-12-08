#pragma once

#include "RenderItem.hpp"
#include "RenderSceneBuilder.hpp"
#include <SceneUpdate.hpp>
#include <gmock/gmock.h>
#include <memory>

class MockRenderSceneBuilder : public RenderSceneBuilder
{
public:
    MOCK_METHOD(void, build, (const SceneUpdate&), (override));
    MOCK_METHOD(RenderItems, popRenderItems, (), (override));
};
