#pragma once

#include "RenderItem.hpp"
#include <SceneItem.hpp>
#include <gmock/gmock.h>
#include <memory>

class MockRenderItem : public RenderItem
{
public:
    MOCK_METHOD(void, render, (), (override));
    MOCK_METHOD(SceneItemId, getId, (), (const, override));
    MOCK_METHOD(void, setPosition, (Position), (override));
    MOCK_METHOD(Position, getPosition, (), (const, override));
    MOCK_METHOD(void, setRotation, (Rotation), (override));
    MOCK_METHOD(Rotation, getRotation, (), (const, override));
};
