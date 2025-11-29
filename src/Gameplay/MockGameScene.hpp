#pragma once

#include "GameScene.hpp"
#include "GameSceneUpdate.hpp"
#include <gmock/gmock.h>

class MockGameScene : public GameScene
{
public:
    MOCK_METHOD(void, show, ());
    MOCK_METHOD(void, hide, ());
    MOCK_METHOD(void, update, (const GameSceneUpdate&));
};
