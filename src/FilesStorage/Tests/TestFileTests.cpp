#include <TextFile.h>
#include <gtest/gtest.h>

class TextFileTests : public testing::Test
{
public:
    static void ASSERT_CONTENT(
        const TextFileContent& expected,
        const TextFileContent& result
    )
    {
        ASSERT_EQ(expected.size(), result.size());

        auto expectedLine { std::begin(expected) };
        for (const auto& resultLine : result)
        {
            ASSERT_EQ(*expectedLine, resultLine);
            expectedLine++;
        }
    }
};

TEST_F(TextFileTests, defaultConstructor_OnlyDefaultValues_ShouldReturnEmptyPathAndContent)
{
    TextFile file;

    EXPECT_EQ("", file.getPath());
    EXPECT_EQ(0, file.getContent().size());
}

TEST_F(TextFileTests, constructor_InputCorrectValues_ShouldReturnFilledPathAndContent)
{
    TextFileContent expectedContent { "testText" };

    TextFile file { "/file/path/text1.txt", "testText" };

    EXPECT_EQ("/file/path/text1.txt", file.getPath());
    ASSERT_CONTENT(expectedContent, file.getContent());
}

TEST_F(TextFileTests, constructor_InputTwoLinesFileContent_ShouldReturnTwoElementsContent)
{
    TextFileContent expectedContent { "testText line 1", "testText line 2" };

    TextFile file { "/file/path/text1.txt",
                    "testText line 1\n"
                    "testText line 2" };

    EXPECT_EQ("/file/path/text1.txt", file.getPath());
    ASSERT_CONTENT(expectedContent, file.getContent());
}

TEST_F(TextFileTests, constructor_InputTwoLinesFileContentWithNextLineOnTheEndOfTheFile_ShouldReturnTwoElementsContent)
{
    TextFileContent expectedContent { "testText line 1", "testText line 2" };

    TextFile file { "/file/path/text1.txt",
                    "testText line 1\n"
                    "testText line 2\n" };

    EXPECT_EQ("/file/path/text1.txt", file.getPath());
    ASSERT_CONTENT(expectedContent, file.getContent());
}

TEST_F(TextFileTests, constructor_InputTwoLinesFileContentWithTwoNextLinesOnTheEndOfTheFile_)
{
    TextFileContent expectedContent { "testText line 1", "testText line 2" };

    TextFile file { "/file/path/text1.txt",
                    "testText line 1\n"
                    "testText line 2\n"
                    "\n" };

    EXPECT_EQ("/file/path/text1.txt", file.getPath());
    ASSERT_CONTENT(expectedContent, file.getContent());
}

TEST_F(TextFileTests, constructor_InputTwoLinesFileContentWithNexLineOnTheBegining_ShouldReturnTwoElementsContent)
{
    TextFileContent expectedContent { "testText line 1", "testText line 2" };

    TextFile file { "/file/path/text1.txt",
                    "\n"
                    "testText line 1\n"
                    "testText line 2" };

    EXPECT_EQ("/file/path/text1.txt", file.getPath());
    ASSERT_CONTENT(expectedContent, file.getContent());
}

TEST_F(TextFileTests, constructor_InputTwoLinesFileContentWithEmptyLineInTheMiddle_ShouldReturnTwoElementsContent)
{
    TextFileContent expectedContent { "testText line 1", "testText line 2" };

    TextFile file { "/file/path/text1.txt",
                    "testText line 1\n"
                    "\n"
                    "testText line 2" };

    EXPECT_EQ("/file/path/text1.txt", file.getPath());
    ASSERT_CONTENT(expectedContent, file.getContent());
}

TEST_F(TextFileTests, constructor_InputFiveLinesFileContentWithFewEmptyLines_ShouldReturnFiveElementsContent)
{
    TextFileContent expectedContent { "testText line 1",
                                      "testText line 2",
                                      "text in line 3",
                                      "blabla bla\tbla",
                                      "test test: 456;" };

    TextFile file { "/file/path/text1.txt",
                    "\n"
                    "\n"
                    "testText line 1\n"
                    "testText line 2\n"
                    "\n"
                    "text in line 3\n"
                    "blabla bla\tbla\n"
                    "\n"
                    "test test: 456;" };

    EXPECT_EQ("/file/path/text1.txt", file.getPath());
    ASSERT_CONTENT(expectedContent, file.getContent());
}
