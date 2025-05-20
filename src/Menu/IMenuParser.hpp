#pragma once

#include "Menus.hpp"
#include <IFileLoader.hpp>
#include <TextFile.hpp>
#include <memory>

class IMenuParser
{
public:
    virtual ~IMenuParser() = default;

    virtual auto parse(std::unique_ptr<IFileLoader<TextFile>> input) -> Menus&& = 0;
};
