#ifndef IMENU_PARSER_HPP
#define IMENU_PARSER_HPP

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

#endif // IMENU_PARSER_HPP
