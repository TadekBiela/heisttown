#pragma once

#include "Menus.hpp"
#include <IFileLoader.hpp>
#include <TextFile.hpp>
#include <memory>

class IMenuParser
{
public:
    virtual ~IMenuParser() = default;

    virtual Menus&& parse(std::unique_ptr<IFileLoader<TextFile>> input) = 0;
};
