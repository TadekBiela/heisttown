#pragma once

#include "SfmlRenderItem.hpp"
#include <SceneItem.hpp>
#include <gmock/gmock.h>
#include <memory>

class MockSfmlRenderItem : public SfmlRenderItem
{
public:
    using SfmlRenderItem::SfmlRenderItem;

    MOCK_METHOD(void, render, (), (override));
    MOCK_METHOD(SceneItemId, getId, (), (const, override));
    MOCK_METHOD(void, setPosition, (Position), (override));
    MOCK_METHOD(void, setRotation, (Rotation), (override));
};
