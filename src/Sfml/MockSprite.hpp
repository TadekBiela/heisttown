#pragma once

#include "Sprite.hpp"
#include <GameObject.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <gmock/gmock.h>

class MockSprite : public Sprite
{
public:
    MockSprite()
        : Sprite(0, sf::Texture{}, {0, 0}, 0)
    {}

    MOCK_METHOD(void, draw, (sf::RenderTarget&), (const, override));
    MOCK_METHOD(GoId, getId, (), (const));
    MOCK_METHOD(void, setPosition, (Position));
    MOCK_METHOD(void, setRotation, (Rotation));
};
