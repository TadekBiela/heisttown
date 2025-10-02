#include "LabelWidget.hpp"
#include <ButtonWidget.hpp>
#include <SFML/Graphics/Font.hpp>
#include <WidgetControl.hpp>
#include <WidgetGeometry.hpp>
#include <WidgetType.hpp>
#include <WidgetsFactorySfml.hpp>
#include <filesystem>
#include <gtest/gtest.h>
#include <memory>

using namespace testing;

class WidgetsFactorySfmlTests : public Test
{
public:
    void SetUp() override
    {
        font = std::make_shared<sf::Font>();
        auto currentPath { std::filesystem::current_path() };
        currentPath = currentPath.parent_path();
        const auto fontPath { currentPath.string() + "/Font/PixelCode.ttf" };
        font->loadFromFile(fontPath);
    }

    std::shared_ptr<sf::Font> getFont()
    {
        return font;
    }

private:
    std::shared_ptr<sf::Font> font;
};

TEST_F(WidgetsFactorySfmlTests, create_LabelType_CreateLabelWidget)
{
    const auto renderer { std::make_shared<Renderer>(1, 1) };
    const auto eventDispatcher { std::make_shared<EventDispatcher>() };
    WidgetsFactorySfml factory { getFont(), renderer, eventDispatcher };

    const auto resultWidget {
        factory.create(
            WidgetType::LABEL,
            WidgetGeometry {},
            WidgetText {},
            WidgetStyle {}
        )
    };

    EXPECT_EQ(WidgetType::LABEL, resultWidget->getType());
    EXPECT_TRUE(dynamic_cast<LabelWidget*>(resultWidget.get()) != nullptr);
}

TEST_F(WidgetsFactorySfmlTests, create_ButtonType_CreateButtonWidget)
{
    const auto renderer { std::make_shared<Renderer>(1, 1) };
    const auto eventDispatcher { std::make_shared<EventDispatcher>() };
    WidgetsFactorySfml factory { getFont(), renderer, eventDispatcher };

    const auto resultWidget {
        factory.create(
            WidgetType::BUTTON,
            WidgetGeometry {},
            WidgetText {},
            WidgetStyle {}
        )
    };

    EXPECT_EQ(WidgetType::BUTTON, resultWidget->getType());
    EXPECT_TRUE(dynamic_cast<ButtonWidget*>(resultWidget.get()) != nullptr);
}
