#pragma once

#include "GameObject.hpp"
#include "GameObjectFactory.hpp"
#include <gmock/gmock.h>
#include <memory>

class MockGameObjectFactory : public GameObjectFactory
{
public:
    MOCK_METHOD(std::shared_ptr<GameObject>, create, (Position, Rotation), (const));
};
