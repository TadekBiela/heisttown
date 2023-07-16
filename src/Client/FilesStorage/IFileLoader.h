#ifndef IFILE_STORAGE_H
#define IFILE_STORAGE_H

#include <filesystem>
#include <map>
#include <string>

using Directory = std::filesystem::path;
using FileName = std::string;

template<typename File>
class IFileLoader
{
public:
    virtual ~IFileLoader() = default;

    virtual const std::map<FileName, File>& getLoadedData() const = 0;
};

#endif //IFILE_STORAGE_H
