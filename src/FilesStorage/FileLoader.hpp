#pragma once

#include "IFileLoader.hpp"
#include <filesystem>
#include <map>
#include <string>

template <typename File>
class FileLoader : public IFileLoader<File>
{
public:
    explicit FileLoader(const Directory& directory)
    {
        const std::string fileDirectory { directory.string() };
        for (const auto& file : std::filesystem::directory_iterator(directory))
        {
            const std::string fullFileName { file.path().filename().string() };
            const std::string filePath { fileDirectory + fullFileName };
            const std::string fileName { file.path().stem().string() };
            loadedData[fileName] = File { filePath.c_str() };
        }
    }

    virtual ~FileLoader() = default;

    const std::map<FileName, File>& getLoadedData() const override
    {
        return loadedData;
    }

protected:
    std::map<FileName, File> loadedData;
};
