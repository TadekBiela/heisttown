#pragma once

#include "SceneItem.hpp"
#include "SceneItemFactory.hpp"
#include <gmock/gmock.h>

class MockSceneItemFactory : public SceneItemFactory
{
public:
    MOCK_METHOD(SceneItem, create, (const SceneItemType&, const Position&, const Rotation&), (override));
};
