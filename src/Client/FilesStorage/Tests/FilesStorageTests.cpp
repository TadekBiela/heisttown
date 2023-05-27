#include <gtest/gtest.h>
#include <FilesStorage.h>
#include <QImage>
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
    QImage expected;
    std::unique_ptr<StubFileLoader<QImage>> loader = std::make_unique<StubFileLoader<QImage>>(std::filesystem::path());
    FilesStorage<QImage> storage{loader.get()};

    QImage result = storage.getFile("default");

    EXPECT_EQ(expected.size().width(), result.size().width());
    EXPECT_EQ(expected.size().height(), result.size().height());
}

TEST_F(FilesStorageTests, getFile_DirectoryContainsOneFileTryGetItByName_ShouldReturnCorrectImageFile)
{
    QImage expected{QSize{50, 30}, QImage::Format_RGB32};
    std::unique_ptr<StubFileLoader<QImage>> loader = std::make_unique<StubFileLoader<QImage>>(std::filesystem::path());
    std::map<FileName, QImage> filesMapWithOneFile{ {"fileOne", expected} };
    loader->setLoadedData(filesMapWithOneFile);
    FilesStorage<QImage> storage{loader.get()};

    QImage result = storage.getFile("fileOne");

    EXPECT_EQ(expected.size().width(), result.size().width());
    EXPECT_EQ(expected.size().height(), result.size().height());
}

TEST_F(FilesStorageTests, getFile_DirectoryContainsOneFileTryGetFileThatNotExist_ShouldReturnEmptyImageFile)
{
    QImage expected;
    std::unique_ptr<StubFileLoader<QImage>> loader = std::make_unique<StubFileLoader<QImage>>(std::filesystem::path());
    std::map<FileName, QImage> filesMapWithOneFile{ {"fileOne", expected} };
    loader->setLoadedData(filesMapWithOneFile);
    FilesStorage<QImage> storage{loader.get()};

    QImage result = storage.getFile("fileThatShoudn'tExist");

    EXPECT_EQ(expected.size().width(), result.size().width());
    EXPECT_EQ(expected.size().height(), result.size().height());
}

TEST_F(FilesStorageTests, getFile_DirectoryContainThreeFilesMiddleFileName_ShouldReturnMiddleImageFile)
{
    QImage expected{QSize{50, 30}, QImage::Format_RGB32};
    std::unique_ptr<StubFileLoader<QImage>> loader = std::make_unique<StubFileLoader<QImage>>(std::filesystem::path());
    std::map<FileName, QImage> filesMapWithOneFile{
        {"frontFile", QImage(QSize{50, 30}, QImage::Format_RGB32)},
        {"middleFile", expected},
        {"backFile", QImage(QSize{40, 80}, QImage::Format_RGB32)}
    };
    loader->setLoadedData(filesMapWithOneFile);
    FilesStorage<QImage> storage{loader.get()};

    QImage result = storage.getFile("middleFile");

    EXPECT_EQ(expected.size().width(), result.size().width());
    EXPECT_EQ(expected.size().height(), result.size().height());
}
