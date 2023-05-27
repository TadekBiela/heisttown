#ifndef STUB_FILE_STORAGE_H
#define STUB_FILE_STORAGE_H

#include <IFileLoader.h>

template<typename File>
class StubFileLoader : public IFileLoader<File>
{
public:
    StubFileLoader(const Directory& directory) {}
    virtual ~StubFileLoader() {}

    const std::map<FileName, File>& getLoadedData() const override
    {
        return loadedData;
    }
    void setLoadedData(const std::map<FileName, File>& newData)
    {
        loadedData = newData;
    }

protected:
    std::map<FileName, File> loadedData;
};

#endif //STUB_FILE_STORAGE_H