#ifndef IMENU_PARSER_H
#define IMENU_PARSER_H

#include "Menus.h"
#include <IFileLoader.h>
#include <TextFile.h>
#include <memory>

class IMenuParser
{
public:
    virtual ~IMenuParser() = default;

    virtual auto parse(std::unique_ptr<IFileLoader<TextFile>> input) -> Menus = 0;
};

#endif // IMENU_PARSER_H
