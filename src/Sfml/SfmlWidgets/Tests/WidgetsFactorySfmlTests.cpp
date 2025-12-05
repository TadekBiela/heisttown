#include "../MockDisplaySfml.hpp"
#include "ButtonWidget.hpp"
#include "LabelWidget.hpp"
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
};

TEST_F(WidgetsFactorySfmlTests, create_LabelType_CreateLabelWidget)
{
    const auto displaySfml { std::make_shared<MockDisplaySfml>() };
    EXPECT_CALL(*displaySfml, addDrawable(_));
    WidgetsFactorySfml factory { nullptr, displaySfml };

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
    WidgetsFactorySfml factory { nullptr, displaySfml };

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
