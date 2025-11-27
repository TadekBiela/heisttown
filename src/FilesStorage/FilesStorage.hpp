#pragma once

#include "IFileLoader.hpp"
#include <map>
#include <memory>

template <typename File>
class FilesStorage
{
public:
    explicit FilesStorage(std::unique_ptr<IFileLoader<File>> fileLoader)
        : data(fileLoader->getLoadedData())
    {
    }
    virtual ~FilesStorage() = default;

    auto getFile(FileName name) const
    {
        if (auto file = data.find(name); file != data.end())
        {
            return file->second;
        }
        return File();
    }

protected:
    std::map<FileName, File> data;
};
