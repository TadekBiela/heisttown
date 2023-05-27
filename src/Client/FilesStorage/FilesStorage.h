#ifndef FILES_STORAGE_H
#define FILES_STORAGE_H

#include <filesystem>
#include <map>
#include <string>
#include <QImage>
#include <QString>

typedef std::filesystem::path Directory;
typedef std::string FileName;

template<typename File>
class IFileLoader
{
public:
    virtual ~IFileLoader() {}

    virtual const std::map<FileName, File>& getLoadedData() const = 0;
};


template<typename File>
class FileLoader : public IFileLoader<File>
{
public:
    FileLoader(const Directory& directory)
    {
        //    const std::filesystem::path filesDirectory{std::filesystem::current_path().string().append(directory)};
        std::string fileDirectory = directory.string();
        for (const auto& file : std::filesystem::directory_iterator(directory)) {
            std::string fullFileName = file.path().filename().string();
            std::string filePath(fileDirectory + fullFileName);
            std::string fileName = file.path().stem().string();
            loadedData[fileName] = File(QString(filePath.c_str()));
        }
    }

    virtual ~FileLoader() {}

    const std::map<FileName, File>& getLoadedData() const override
    {
        return loadedData;
    }

protected:
    std::map<FileName, File> loadedData;
};

template<typename File>
class StubFileLoader : public IFileLoader<File>
{
public:
    StubFileLoader(const Directory& directory) {}
    virtual ~StubFileLoader() {}

    const std::map<FileName, File>& getLoadedData() const override
    {
        return loadedData;
    }
    void setLoadedData(const std::map<FileName, File>& newData)
    {
        loadedData = newData;
    }

protected:
    std::map<FileName, File> loadedData;
};

template<typename File>
class FilesStorage
{
public:
    FilesStorage(IFileLoader<QImage> const* fileLoader)
    {
        data = fileLoader->getLoadedData();
    }

    virtual ~FilesStorage() {}

    File getFile(FileName name) const
    {
        if(auto file = data.find(name); file != data.end())
        {
            return file->second;
        }
        return QImage();
    }

protected:
    std::map<FileName, File> data;
};

#endif //FILES_STORAGE_H
