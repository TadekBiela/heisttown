#ifndef FILES_STORAGE_H
#define FILES_STORAGE_H

#include <filesystem>
#include <map>
#include <string>
#include <QImage>

typedef QImage File;

typedef std::filesystem::path Directory;
typedef std::string FileName;
typedef std::map<FileName, File> FilesMap;

class IFileLoader
{
public:
    virtual ~IFileLoader() {}

    virtual FilesMap getLoadedData() const = 0;

protected:
    FilesMap loadedData;
};

class FileLoader : public IFileLoader
{
public:
    FileLoader(const Directory& directory);
    virtual ~FileLoader();

    FilesMap getLoadedData() const override;
};

class StubFileLoader : public IFileLoader
{
public:
    StubFileLoader(const Directory& directory);
    virtual ~StubFileLoader();

    FilesMap getLoadedData() const override;
    void setLoadedData(FilesMap newData);
};


class FilesStorage
{
public:
    FilesStorage(const IFileLoader* fileLoader);
    virtual ~FilesStorage();

    File getFile(FileName name) const;

protected:
    FilesMap data;
};

#endif //FILES_STORAGE_H
