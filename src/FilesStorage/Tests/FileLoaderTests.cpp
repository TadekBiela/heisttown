#include <FileLoader.hpp>
#include <IFileLoader.hpp>
#include <TextFile.hpp>
#include <filesystem>
#include <gtest/gtest.h>
#include <stdexcept>

class FileLoaderTests : public testing::Test
{
};

TEST_F(FileLoaderTests, constructor_DirectoryContainsThreeFiles_ShouldLoadThreeFiles)
{
    const Directory inputDirectory { std::filesystem::current_path().string() + "/TestFiles/" };

    const FileLoader<TextFile> loader { inputDirectory };

    const auto& result = loader.getLoadedData();
    EXPECT_EQ(3, result.size());
    ASSERT_EQ(1, result.count("test1"));
    EXPECT_EQ(0, result.at("test1").getContent().size());
    ASSERT_EQ(1, result.count("test2"));
    EXPECT_EQ(5, result.at("test2").getContent().size());
    ASSERT_EQ(1, result.count("test3"));
    EXPECT_EQ(10, result.at("test3").getContent().size());
}

TEST_F(FileLoaderTests, constructor_WrongDirectory_ShouldThrowException)
{
    ASSERT_THROW(FileLoader<TextFile> { "wrong/directory/" }, std::runtime_error);
}
