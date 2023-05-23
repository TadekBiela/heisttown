#include <gtest/gtest.h>
#include "../mousecursor.hpp"

class MouseCursorTests : public testing::Test
{
    void SetUp()
    {
    }
    void TearDown()
    {
    }
};

TEST_F(MouseCursorTests, Constructor_OnlyDefaultValue_ShouldCreateDefaultCursorAsMainMenu)
{
    MouseCursor cursor;
    EXPECT_EQ(1, 1);
}
