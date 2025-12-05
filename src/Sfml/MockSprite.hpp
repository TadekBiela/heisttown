#pragma once

#include "Sprite.hpp"
#include <SceneItem.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <gmock/gmock.h>

class MockSprite : public Sprite
{
public:
    MockSprite()
        : Sprite(0, sf::Texture{}, {0, 0}, 0)
    {}

    MOCK_METHOD(void, draw, (sf::RenderTarget&), (const, override));
    MOCK_METHOD(SceneItemId, getId, (), (const, override));
    MOCK_METHOD(void, setPosition, (Position), (override));
    MOCK_METHOD(void, setRotation, (Rotation), (override));
};
