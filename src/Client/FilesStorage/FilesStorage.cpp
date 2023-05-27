#include "FilesStorage.h"

FilesStorage::FilesStorage(IFileLoader<QImage> const* fileLoader)
{
    data = fileLoader->getLoadedData();
}

FilesStorage::~FilesStorage()
{
}

QImage FilesStorage::getFile(FileName name) const
{
    if(auto file = data.find(name); file != data.end())
    {
        return file->second;
    }
    return QImage();
}
