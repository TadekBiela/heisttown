#include <QtWidgetsFactory.h>
#include <WidgetGeometry.h>
#include <WidgetType.h>
#include <gtest/gtest.h>

class QtWidgetsFactoryTests : public testing::Test
{
public:
    void SetUp() override
    {
    }
    void TearDown() override
    {
    }
};

TEST_F(QtWidgetsFactoryTests, create_ButtonType_ShouldReturnButtonObject)
{
    WidgetGeometry expectedGeometry { 100, 40, 120, 30 };
    QtWidgetsFactory factory;

    auto result = factory.create(WidgetType::BUTTON, expectedGeometry, "test", "");

    EXPECT_EQ(WidgetType::BUTTON, result->type());
    EXPECT_EQ(expectedGeometry, result->geometry());
    EXPECT_EQ("test", result->text());
    EXPECT_EQ("", result->style());
}
