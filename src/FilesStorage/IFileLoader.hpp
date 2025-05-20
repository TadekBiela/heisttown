#pragma once

#include <filesystem>
#include <map>
#include <string>

using Directory = std::filesystem::path;
using FileName = std::string;

template <typename File>
class IFileLoader
{
public:
    virtual ~IFileLoader() = default;

    virtual const std::map<FileName, File>& getLoadedData() const = 0;
};
