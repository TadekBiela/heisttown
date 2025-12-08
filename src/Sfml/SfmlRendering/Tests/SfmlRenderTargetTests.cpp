#include "SfmlRenderTarget.hpp"
#include <MockRenderItem.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <gtest/gtest.h>
#include <memory>

using namespace testing;

class SfmlRenderTargetTests : public Test
{
public:
    sf::RenderWindow& getWindow()
    {
        return window;
    }

    static std::unique_ptr<MockRenderItem> getMockRenderItem()
    {
        auto item { std::make_unique<MockRenderItem>() };
        EXPECT_CALL(*item, render());
        return item;
    }

private:
    sf::RenderWindow window;
};

TEST_F(SfmlRenderTargetTests, render_EmptyRenderItems_DoNothing)
{
    SfmlRenderTarget target { getWindow() };

    target.render({});
}

TEST_F(SfmlRenderTargetTests, render_RenderItemsWithOneItem_RenderOneItem)
{
    RenderItems items;
    items.push_back(getMockRenderItem());
    SfmlRenderTarget target { getWindow() };

    target.render(items);
}

TEST_F(SfmlRenderTargetTests, render_RenderItemsWithThreeItems_RenderAllItems)
{
    RenderItems items;
    items.push_back(getMockRenderItem());
    items.push_back(getMockRenderItem());
    items.push_back(getMockRenderItem());
    SfmlRenderTarget target { getWindow() };

    target.render(items);
}
