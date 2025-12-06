#pragma once

#include "SfmlRenderItem.hpp"
#include "SfmlRenderItem.hpp"
#include <SceneItem.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <gmock/gmock.h>
#include <memory>

class MockSfmlRenderItem : public SfmlRenderItem
{
public:
    MockSfmlRenderItem()
        : SfmlRenderItem(window, 0, texutre, { 0.0F, 0.0F}, 0.0F)
    {}

    MOCK_METHOD(void, render, (), (override));
    MOCK_METHOD(SceneItemId, getId, (), (const, override));
    MOCK_METHOD(void, setPosition, (Position), (override));
    MOCK_METHOD(void, setRotation, (Rotation), (override));

private:
    sf::RenderWindow window;
    sf::Texture texutre;
};
