#include <TextFile.hpp>
#include <filesystem>
#include <gtest/gtest.h>
#include <iterator>
#include <stdexcept>
#include <string>

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
    const TextFile file;

    EXPECT_EQ("", file.getPath());
    EXPECT_EQ(0, file.getContent().size());
}

TEST_F(TextFileTests, constructor_WrongFilePathWithoutRawContent_ShouldThrowException)
{
    ASSERT_THROW(TextFile { "wrong/file/path.txt" }, std::runtime_error);
}

TEST_F(TextFileTests, constructor_CorrectFilePathFile_ShouldOpenRealFileAndLoadContent)
{
    const std::string expectedFilePath { std::filesystem::current_path().string() + "/TestFiles/test3.txt" };
    const TextFileContent expectedContent { "Button: {",
                                            "    geometry: 130, 30, 500, 80",
                                            "    text: testText1",
                                            "    style: none",
                                            "}",
                                            "Button: {",
                                            "    geometry: 130, 30, 500, 160",
                                            "    text: testText2",
                                            "    style: none",
                                            "}" };

    const TextFile file(expectedFilePath);

    EXPECT_EQ(expectedFilePath, file.getPath());
    ASSERT_CONTENT(expectedContent, file.getContent());
}

TEST_F(TextFileTests, constructor_InputCorrectValues_ShouldReturnFilledPathAndContent)
{
    const TextFileContent expectedContent { "testText" };

    const TextFile file { "/file/path/text1.txt", "testText" };

    EXPECT_EQ("/file/path/text1.txt", file.getPath());
    ASSERT_CONTENT(expectedContent, file.getContent());
}

TEST_F(TextFileTests, constructor_InputTwoLinesFileContent_ShouldReturnTwoElementsContent)
{
    const TextFileContent expectedContent { "testText line 1", "testText line 2" };

    const TextFile file { "/file/path/text1.txt",
                          "testText line 1\n"
                          "testText line 2" };

    EXPECT_EQ("/file/path/text1.txt", file.getPath());
    ASSERT_CONTENT(expectedContent, file.getContent());
}

TEST_F(TextFileTests, constructor_InputTwoLinesFileContentWithNextLineOnTheEndOfTheFile_ShouldReturnTwoElementsContent)
{
    const TextFileContent expectedContent { "testText line 1", "testText line 2" };

    const TextFile file { "/file/path/text1.txt",
                          "testText line 1\n"
                          "testText line 2\n" };

    EXPECT_EQ("/file/path/text1.txt", file.getPath());
    ASSERT_CONTENT(expectedContent, file.getContent());
}

TEST_F(TextFileTests, constructor_InputTwoLinesFileContentWithTwoNextLinesOnTheEndOfTheFile_)
{
    const TextFileContent expectedContent { "testText line 1", "testText line 2" };

    const TextFile file { "/file/path/text1.txt",
                          "testText line 1\n"
                          "testText line 2\n"
                          "\n" };

    EXPECT_EQ("/file/path/text1.txt", file.getPath());
    ASSERT_CONTENT(expectedContent, file.getContent());
}

TEST_F(TextFileTests, constructor_InputTwoLinesFileContentWithNexLineOnTheBegining_ShouldReturnTwoElementsContent)
{
    const TextFileContent expectedContent { "testText line 1", "testText line 2" };

    const TextFile file { "/file/path/text1.txt",
                          "\n"
                          "testText line 1\n"
                          "testText line 2" };

    EXPECT_EQ("/file/path/text1.txt", file.getPath());
    ASSERT_CONTENT(expectedContent, file.getContent());
}

TEST_F(TextFileTests, constructor_InputTwoLinesFileContentWithEmptyLineInTheMiddle_ShouldReturnTwoElementsContent)
{
    const TextFileContent expectedContent { "testText line 1", "testText line 2" };

    const TextFile file { "/file/path/text1.txt",
                          "testText line 1\n"
                          "\n"
                          "testText line 2" };

    EXPECT_EQ("/file/path/text1.txt", file.getPath());
    ASSERT_CONTENT(expectedContent, file.getContent());
}

TEST_F(TextFileTests, constructor_InputFiveLinesFileContentWithFewEmptyLines_ShouldReturnFiveElementsContent)
{
    const TextFileContent expectedContent { "testText line 1",
                                            "testText line 2",
                                            "text in line 3",
                                            "blabla bla\tbla",
                                            "test test: 456;" };

    const TextFile file { "/file/path/text1.txt",
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
