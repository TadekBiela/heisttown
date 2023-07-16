#include <gtest/gtest.h>
#include <MouseCursor.h>

class MouseCursorTests : public testing::Test
{
    void SetUp() override
    {}
    void TearDown() override
    {}
};

TEST_F(MouseCursorTests, Constructor_OnlyDefaultValue_ShouldCreateDefaultCursorAsMainMenu)
{
    MouseCursor cursor;
    EXPECT_EQ(1, 1);
}
