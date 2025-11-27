#include <FilesStorage.hpp>
#include <IFileLoader.hpp>
#include <MockFileLoader.hpp>
#include <TextFile.hpp>
#include <gtest/gtest.h>
#include <map>
#include <memory>

using namespace testing;

class FilesStorageTests : public testing::Test
{
};

TEST_F(FilesStorageTests, getFile_OnlyDefaultValue_ShouldReturnEmptyImageFile)
{
    const TextFile expected;
    const std::map<FileName, TextFile> emptyFileConent {};
    auto loader { std::make_unique<MockFileLoader<TextFile>>() };
    EXPECT_CALL(*loader, getLoadedData()).WillOnce(ReturnRef(emptyFileConent));
    const FilesStorage<TextFile> storage { std::move(loader)};

    const TextFile result = storage.getFile("default");

    EXPECT_EQ(expected.getContent(), result.getContent());
    EXPECT_EQ(expected.getPath(), result.getPath());
}

TEST_F(FilesStorageTests, getFile_DirectoryContainsOneFileTryGetItByName_ShouldReturnCorrectImageFile)
{
    const TextFile expected { "/file/path/text1.txt", "testText" };
    const std::map<FileName, TextFile> filesMapWithOneFile { { "fileOne", expected } };
    auto loader { std::make_unique<MockFileLoader<TextFile>>() };
    EXPECT_CALL(*loader, getLoadedData()).WillOnce(ReturnRef(filesMapWithOneFile));
    const FilesStorage<TextFile> storage { std::move(loader)};

    const TextFile result = storage.getFile("fileOne");

    EXPECT_EQ(expected.getContent(), result.getContent());
    EXPECT_EQ(expected.getPath(), result.getPath());
}

TEST_F(FilesStorageTests, getFile_DirectoryContainsOneFileTryGetFileThatNotExist_ShouldReturnEmptyImageFile)
{
    const TextFile expected;
    const std::map<FileName, TextFile> filesMapWithOneFile { { "fileOne", expected } };
    auto loader { std::make_unique<MockFileLoader<TextFile>>() };
    EXPECT_CALL(*loader, getLoadedData()).WillOnce(ReturnRef(filesMapWithOneFile));
    const FilesStorage<TextFile> storage { std::move(loader)};

    const TextFile result = storage.getFile("fileThatShoudn'tExist");

    EXPECT_EQ(expected.getPath(), result.getPath());
    EXPECT_EQ(expected.getContent(), result.getContent());
}

TEST_F(FilesStorageTests, getFile_DirectoryContainThreeFilesMiddleFileName_ShouldReturnMiddleImageFile)
{
    const TextFile expected { "/file/path/text1.txt", "testText" };
    const std::map<FileName, TextFile> filesMapWithOneFile {
        { "frontFile", TextFile { "/file/path/text0.txt", "000000000" } },
        { "middleFile", expected },
        { "backFile", TextFile { "/file/path/text2.txt", "2222222" } }
    };
    auto loader { std::make_unique<MockFileLoader<TextFile>>() };
    EXPECT_CALL(*loader, getLoadedData()).WillOnce(ReturnRef(filesMapWithOneFile));
    const FilesStorage<TextFile> storage { std::move(loader)};

    const TextFile result = storage.getFile("middleFile");

    EXPECT_EQ(expected.getPath(), result.getPath());
    EXPECT_EQ(expected.getContent(), result.getContent());
}
