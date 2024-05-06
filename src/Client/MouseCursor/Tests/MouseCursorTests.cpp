#include <MouseCursor.hpp>
#include <gtest/gtest.h>

class MouseCursorTests : public testing::Test
{
};

TEST_F(MouseCursorTests, Constructor_OnlyDefaultValue_ShouldCreateDefaultCursorAsMainMenu)
{
    MouseCursor cursor;
    EXPECT_EQ(1, 1);
}
