#pragma once

#include "IFileLoader.hpp"

template <typename File>
class FilesStorage
{
public:
    explicit FilesStorage(IFileLoader<File> const* fileLoader)
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
