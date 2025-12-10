#pragma once

#include "SfmlWindow.hpp"
#include <InputDispatcher.hpp>
#include <SceneUpdate.hpp>
#include <gmock/gmock.h>
#include <memory>

class MockSfmlWindow : public SfmlWindow
{
public:
    MockSfmlWindow()
        : SfmlWindow(1, 1, nullptr)
    {}

    MOCK_METHOD(void, add, (std::shared_ptr<RenderItem>), (override));
    MOCK_METHOD(sf::RenderTarget&, getRenderTarget, (), (override));
    MOCK_METHOD(std::shared_ptr<InputDispatcher>, getDispatcher,(), (override));
    MOCK_METHOD(void, display, (), (override));
    MOCK_METHOD(void, show, (), (override));
    MOCK_METHOD(void, hide, (), (override));
    MOCK_METHOD(void, update, (const SceneUpdate&), (override));
};
