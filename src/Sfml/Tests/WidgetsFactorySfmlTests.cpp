#include "ButtonWidget.hpp"
#include "LabelWidget.hpp"
#include "MockDisplaySfml.hpp"
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
    const auto displaySfml { std::make_shared<MockDisplaySfml>() };
    EXPECT_CALL(*displaySfml, addDrawable(_));
    WidgetsFactorySfml factory { getFont(), displaySfml };

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
    const auto displaySfml { std::make_shared<MockDisplaySfml>() };
    EXPECT_CALL(*displaySfml, addDrawable(_));
    EXPECT_CALL(*displaySfml, addEventHandler(_));
    WidgetsFactorySfml factory { getFont(), displaySfml };

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
