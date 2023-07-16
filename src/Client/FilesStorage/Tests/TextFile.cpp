#include "TextFile.h"

TextFile::TextFile(std::string filepath, std::string filecontent)
    : path(std::move(filepath))
    , content(std::move(filecontent))
{
}

auto TextFile::getContent() const -> std::string
{
    return content;
}

auto TextFile::getPath() const -> std::string
{
    return path;
}
