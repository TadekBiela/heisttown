#include <gtest/gtest.h>
#include <FilesStorage.h>
#include <memory>

class FilesStorageTests : public testing::Test
{
    void SetUp()
    {
    }
    void TearDown()
    {
    }
};

TEST_F(FilesStorageTests, getFile_OnlyDefaultValue_ShouldReturnEmptyImageFile)
{
    File expected;
    std::unique_ptr<StubFileLoader> loader = std::make_unique<StubFileLoader>(std::filesystem::path());
    FilesStorage storage{loader.get()};

    File result = storage.getFile("default");

    EXPECT_EQ(expected.size().width(), result.size().width());
    EXPECT_EQ(expected.size().height(), result.size().height());
}

TEST_F(FilesStorageTests, getFile_DirectoryContainsOneFileTryGetItByName_ShouldReturnCorrectImageFile)
{
    File expected{QSize{50, 30}, File::Format_RGB32};
    std::unique_ptr<StubFileLoader> loader = std::make_unique<StubFileLoader>(std::filesystem::path());
    FilesMap filesMapWithOneFile{ {"fileOne", expected} };
    loader->setLoadedData(filesMapWithOneFile);
    FilesStorage storage{loader.get()};

    File result = storage.getFile("fileOne");

    EXPECT_EQ(expected.size().width(), result.size().width());
    EXPECT_EQ(expected.size().height(), result.size().height());
}

TEST_F(FilesStorageTests, getFile_DirectoryContainsOneFileTryGetFileThatNotExist_ShouldReturnEmptyImageFile)
{
    File expected;
    std::unique_ptr<StubFileLoader> loader = std::make_unique<StubFileLoader>(std::filesystem::path());
    FilesMap filesMapWithOneFile{ {"fileOne", expected} };
    loader->setLoadedData(filesMapWithOneFile);
    FilesStorage storage{loader.get()};

    File result = storage.getFile("fileThatShoudn'tExist");

    EXPECT_EQ(expected.size().width(), result.size().width());
    EXPECT_EQ(expected.size().height(), result.size().height());
}

TEST_F(FilesStorageTests, getFile_DirectoryContainThreeFilesMiddleFileName_ShouldReturnMiddleImageFile)
{
    File expected{QSize{50, 30}, File::Format_RGB32};
    std::unique_ptr<StubFileLoader> loader = std::make_unique<StubFileLoader>(std::filesystem::path());
    FilesMap filesMapWithOneFile{
        {"frontFile", File(QSize{50, 30}, File::Format_RGB32)},
        {"middleFile", expected},
        {"backFile", File(QSize{40, 80}, File::Format_RGB32)}
    };
    loader->setLoadedData(filesMapWithOneFile);
    FilesStorage storage{loader.get()};

    File result = storage.getFile("middleFile");

    EXPECT_EQ(expected.size().width(), result.size().width());
    EXPECT_EQ(expected.size().height(), result.size().height());
}
