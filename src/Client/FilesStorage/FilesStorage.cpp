#include "FilesStorage.h"

FileLoader::FileLoader(const Directory& directory)
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

FileLoader::~FileLoader()
{
}

FilesMap FileLoader::getLoadedData() const
{
    return loadedData;
}


StubFileLoader::StubFileLoader(const Directory& directory)
{
}

StubFileLoader::~StubFileLoader()
{
}

FilesMap StubFileLoader::getLoadedData() const
{
    return loadedData;
}

void StubFileLoader::setLoadedData(FilesMap newData)
{
    loadedData = newData;
}



FilesStorage::FilesStorage(const IFileLoader *fileLoader)
{
    data = fileLoader->getLoadedData();
}

FilesStorage::~FilesStorage()
{
}

File FilesStorage::getFile(FileName name) const
{
    if(auto file = data.find(name); file != data.end())
    {
        return file->second;
    }
    return File();
}
