#pragma once

#include "IFileLoader.hpp"

template <typename File>
class StubFileLoader : public IFileLoader<File>
{
public:
    explicit StubFileLoader([[maybe_unused]] const Directory& directory)
    {
    }
    virtual ~StubFileLoader() = default;

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
