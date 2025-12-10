#pragma once

#include "DisplaySfml.hpp"
#include "Drawable.hpp"
#include <InputDispatcher.hpp>
#include <SceneUpdate.hpp>
#include <gmock/gmock.h>
#include <memory>

class MockDisplaySfml : public DisplaySfml
{
public:
    MockDisplaySfml()
        : DisplaySfml(1, 1, nullptr)
    {}

    MOCK_METHOD(void, addDrawable, (std::shared_ptr<Drawable>), (override));
    MOCK_METHOD(std::shared_ptr<InputDispatcher>, getDispatcher,(), (override));
    MOCK_METHOD(void, display, (), (override));
    MOCK_METHOD(void, show, (), (override));
    MOCK_METHOD(void, hide, (), (override));
    MOCK_METHOD(void, update, (const SceneUpdate&), (override));
};
