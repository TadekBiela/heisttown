#pragma once

#include "DisplaySfml.hpp"
#include "Drawable.hpp"
#include "EventHandler.hpp"
#include <GameSceneUpdate.hpp>
#include <gmock/gmock.h>
#include <memory>

class MockDisplaySfml : public DisplaySfml
{
public:
    MockDisplaySfml()
        : DisplaySfml(1, 1)
    {}

    MOCK_METHOD(void, addDrawable, (std::shared_ptr<Drawable>));
    MOCK_METHOD(void, addEventHandler, (std::shared_ptr<EventHandler>));
    MOCK_METHOD(void, display, ());
    MOCK_METHOD(void, update, (const GameSceneUpdate&), (override));
};
