#include <FilesStorage.h>
#include <StubFileLoader.h>
#include <TextFile.h>
#include <gtest/gtest.h>
#include <memory>

class FilesStorageTests : public testing::Test
{
};

TEST_F(FilesStorageTests, getFile_OnlyDefaultValue_ShouldReturnEmptyImageFile)
{
    TextFile expected;
    auto loader = std::make_unique<StubFileLoader<TextFile>>(std::filesystem::path());
    FilesStorage<TextFile> storage { loader.get() };

    TextFile result = storage.getFile("default");

    EXPECT_EQ(expected.getContent(), result.getContent());
    EXPECT_EQ(expected.getPath(), result.getPath());
}

TEST_F(FilesStorageTests, getFile_DirectoryContainsOneFileTryGetItByName_ShouldReturnCorrectImageFile)
{
    TextFile expected { "/file/path/text1.txt", "testText" };
    auto loader = std::make_unique<StubFileLoader<TextFile>>(std::filesystem::path());
    std::map<FileName, TextFile> filesMapWithOneFile { { "fileOne", expected } };
    loader->setLoadedData(filesMapWithOneFile);
    FilesStorage<TextFile> storage { loader.get() };

    TextFile result = storage.getFile("fileOne");

    EXPECT_EQ(expected.getContent(), result.getContent());
    EXPECT_EQ(expected.getPath(), result.getPath());
}

TEST_F(FilesStorageTests, getFile_DirectoryContainsOneFileTryGetFileThatNotExist_ShouldReturnEmptyImageFile)
{
    TextFile expected;
    auto loader = std::make_unique<StubFileLoader<TextFile>>(std::filesystem::path());
    std::map<FileName, TextFile> filesMapWithOneFile { { "fileOne", expected } };
    loader->setLoadedData(filesMapWithOneFile);
    FilesStorage<TextFile> storage { loader.get() };

    TextFile result = storage.getFile("fileThatShoudn'tExist");

    EXPECT_EQ(expected.getPath(), result.getPath());
    EXPECT_EQ(expected.getContent(), result.getContent());
}

TEST_F(FilesStorageTests, getFile_DirectoryContainThreeFilesMiddleFileName_ShouldReturnMiddleImageFile)
{
    TextFile expected { "/file/path/text1.txt", "testText" };
    auto loader = std::make_unique<StubFileLoader<TextFile>>(std::filesystem::path());
    std::map<FileName, TextFile> filesMapWithOneFile {
        { "frontFile", TextFile { "/file/path/text0.txt", "000000000" } },
        { "middleFile", expected },
        { "backFile", TextFile { "/file/path/text2.txt", "2222222" } }
    };
    loader->setLoadedData(filesMapWithOneFile);
    FilesStorage<TextFile> storage { loader.get() };

    TextFile result = storage.getFile("middleFile");

    EXPECT_EQ(expected.getPath(), result.getPath());
    EXPECT_EQ(expected.getContent(), result.getContent());
}
