#include <TextFile.h>
#include <gtest/gtest.h>
#include <memory>

class TextFileTests : public testing::Test
{
    void SetUp() override
    {
    }
    void TearDown() override
    {
    }
};

TEST_F(TextFileTests, defaultConstructor_OnlyDefaultValues_ShouldReturnEmptyContentAndPath)
{
    TextFile file;

    EXPECT_EQ("", file.getContent());
    EXPECT_EQ("", file.getPath());
}

TEST_F(TextFileTests, constructor_InputCorrectValues_ShouldReturnFilledContentAndPath)
{
    TextFile file("/file/path/text1.txt", "testText");

    EXPECT_EQ("testText", file.getContent());
    EXPECT_EQ("/file/path/text1.txt", file.getPath());
}
