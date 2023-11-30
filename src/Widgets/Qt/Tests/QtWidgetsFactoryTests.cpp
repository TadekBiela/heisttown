#include <QtWidgetsFactory.h>
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
    QtWidgetsFactory factory;

    auto result = std::move(factory.create(WidgetType::BUTTON));

    EXPECT_EQ(WidgetType::BUTTON, result->type());
}
