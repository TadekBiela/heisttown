#pragma once

#include "Scene.hpp"
#include "SceneUpdate.hpp"
#include <gmock/gmock.h>

class MockScene : public Scene
{
public:
    MOCK_METHOD(void, show, (), (override));
    MOCK_METHOD(void, hide, (), (override));
    MOCK_METHOD(void, update, (const SceneUpdate&), (override));
};
