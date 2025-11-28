#pragma once

#include "GameObject.hpp"
#include "GameObjectFactory.hpp"
#include <gmock/gmock.h>

class MockGameObjectFactory : public GameObjectFactory
{
public:
    MOCK_METHOD(GameObject, create, (const GoType&, const Position&, const Rotation&));
};
