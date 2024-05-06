#include <QtWidgetsFactory.hpp>
#include <WidgetGeometry.hpp>
#include <WidgetType.hpp>
#include <gtest/gtest.h>

class QtWidgetsFactoryTests : public testing::Test
{
};

TEST_F(QtWidgetsFactoryTests, create_ButtonType_ShouldReturnButtonObject)
{
    WidgetGeometry expectedGeometry { 100, 40, 120, 30 };
    auto display { std::make_shared<QWidget>() };
    QtWidgetsFactory factory(display);

    auto result = factory.create(WidgetType::BUTTON, expectedGeometry, "", "QPushButton: { border: 5px; }");

    EXPECT_EQ(WidgetType::BUTTON, result->type());
    EXPECT_EQ(expectedGeometry, result->geometry());
    EXPECT_EQ("", result->text());
    EXPECT_EQ("QPushButton: { border: 5px; }", result->style());
}

TEST_F(QtWidgetsFactoryTests, create_LabelType_ShouldReturnLabelObject)
{
    WidgetGeometry expectedGeometry { 140, 80, 80, 20 };
    auto display { std::make_shared<QWidget>() };
    QtWidgetsFactory factory(display);

    auto result = factory.create(WidgetType::LABEL, expectedGeometry, "", "QLabel: { border: 3px; }");

    EXPECT_EQ(WidgetType::LABEL, result->type());
    EXPECT_EQ(expectedGeometry, result->geometry());
    EXPECT_EQ("", result->text());
    EXPECT_EQ("QLabel: { border: 3px; }", result->style());
}
