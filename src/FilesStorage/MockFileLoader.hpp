#pragma once

#include "IFileLoader.hpp"
#include <gmock/gmock.h>
#include <map>

template <typename File>
class MockFileLoader : public IFileLoader<File>
{
public:
    MOCK_CONST_METHOD0(getLoadedData, const std::map<FileName, File>&());
};
