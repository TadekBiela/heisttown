#pragma once

#include "GameScene.hpp"
#include "GameSceneUpdate.hpp"
#include <gmock/gmock.h>

class MockGameScene : public GameScene
{
public:
    MOCK_METHOD(void, show, (), (override));
    MOCK_METHOD(void, hide, (), (override));
    MOCK_METHOD(void, update, (const GameSceneUpdate&), (override));
};
