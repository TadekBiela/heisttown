#ifndef FILE_LOADER_H
#define FILE_LOADER_H

#include "IFileLoader.h"

template <typename File>
class FileLoader : public IFileLoader<File>
{
public:
    FileLoader(const Directory& directory)
    {
        std::string fileDirectory = directory.string();
        for (const auto& file : std::filesystem::directory_iterator(directory))
        {
            std::string fullFileName = file.path().filename().string();
            std::string filePath(fileDirectory + fullFileName);
            std::string fileName = file.path().stem().string();
            loadedData[fileName] = File(filePath.c_str());
        }
    }

    virtual ~FileLoader()
    {
    }

    const std::map<FileName, File>& getLoadedData() const override
    {
        return loadedData;
    }

protected:
    std::map<FileName, File> loadedData;
};

#endif // FILE_LOADER_H
