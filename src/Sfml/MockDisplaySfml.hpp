#pragma once

#include "DisplaySfml.hpp"
#include "Drawable.hpp"
#include "EventHandler.hpp"
#include "MockSpriteFactory.hpp"
#include <GameSceneUpdate.hpp>
#include <gmock/gmock.h>
#include <memory>

class MockDisplaySfml : public DisplaySfml
{
public:
    MockDisplaySfml()
        : DisplaySfml(1, 1, nullptr, std::make_unique<MockSpriteFactory>())
    {}

    MOCK_METHOD(void, addDrawable, (std::shared_ptr<Drawable>));
    MOCK_METHOD(void, addEventHandler, (std::shared_ptr<EventHandler>));
    MOCK_METHOD(void, display, ());
    MOCK_METHOD(void, show, ());
    MOCK_METHOD(void, hide, ());
    MOCK_METHOD(void, update, (const GameSceneUpdate&), (override));
};
