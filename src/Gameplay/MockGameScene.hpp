#pragma once

#include "GameScene.hpp"
#include "GameSceneUpdate.hpp"
#include <gmock/gmock.h>

class MockGameScene : public GameScene
{
public:
    MOCK_METHOD1(update, void(const GameSceneUpdate&));
};
