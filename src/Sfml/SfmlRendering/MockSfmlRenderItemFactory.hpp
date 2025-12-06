#pragma once

#include "SfmlRenderItem.hpp"
#include "SfmlRenderItemFactory.hpp"
#include <SceneItem.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <gmock/gmock.h>
#include <memory>

class MockSfmlRenderItemFactory : public SfmlRenderItemFactory
{
public:
    MockSfmlRenderItemFactory()
        : SfmlRenderItemFactory(window, nullptr)
    {}

    MOCK_METHOD(std::unique_ptr<SfmlRenderItem>, create, (const SceneItemType&, const Position&, const Rotation&), (override));

private:
    sf::RenderWindow window;
};
