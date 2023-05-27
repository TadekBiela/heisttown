#ifndef IFILE_STORAGE_H
#define IFILE_STORAGE_H

#include <filesystem>
#include <map>
#include <string>

typedef std::filesystem::path Directory;
typedef std::string FileName;

template<typename File>
class IFileLoader
{
public:
    virtual ~IFileLoader() {}

    virtual const std::map<FileName, File>& getLoadedData() const = 0;
};

#endif //IFILE_STORAGE_H
