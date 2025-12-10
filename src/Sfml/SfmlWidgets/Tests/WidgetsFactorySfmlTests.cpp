#include "../MockSfmlWindow.hpp"
#include "ButtonWidget.hpp"
#include "LabelWidget.hpp"
#include <MockInputDispatcher.hpp>
#include <WidgetControl.hpp>
#include <WidgetGeometry.hpp>
#include <WidgetType.hpp>
#include <WidgetsFactorySfml.hpp>
#include <gtest/gtest.h>
#include <memory>

using namespace testing;

class WidgetsFactorySfmlTests : public Test
{
public:
    sf::RenderWindow& getWindow()
    {
        return window;
    }

private:
    sf::RenderWindow window;
};

TEST_F(WidgetsFactorySfmlTests, create_LabelType_CreateLabelWidget)
{
    const auto sfmlWindow { std::make_shared<MockSfmlWindow>() };
    EXPECT_CALL(*sfmlWindow, getRenderTarget()).WillOnce(ReturnRef(getWindow()));
    EXPECT_CALL(*sfmlWindow, add(_));
    WidgetsFactorySfml factory { nullptr, sfmlWindow, nullptr };

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
    const auto dispatcher { std::make_shared<MockInputDispatcher>() };
    EXPECT_CALL(*dispatcher, addHandler(_));
    const auto sfmlWindow { std::make_shared<MockSfmlWindow>() };
    EXPECT_CALL(*sfmlWindow, getRenderTarget()).WillOnce(ReturnRef(getWindow()));
    EXPECT_CALL(*sfmlWindow, add(_));
    WidgetsFactorySfml factory { nullptr, sfmlWindow, dispatcher };

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

TEST_F(WidgetsFactorySfmlTests, create_UnknownType_ReturnNullptr)
{
    WidgetsFactorySfml factory { nullptr, nullptr, nullptr };

    const auto resultWidget {
        factory.create(
            WidgetType::UNKNOWN,
            WidgetGeometry {},
            WidgetText {},
            WidgetStyle {}
        )
    };

    EXPECT_TRUE(resultWidget == nullptr);
}
