#include "TextFile.h"

TextFile::TextFile(std::string filepath, std::string filecontent) :
    path(filepath),
    content(filecontent)
{
}

TextFile::~TextFile()
{
}

std::string TextFile::getContent() const
{
    return content;
}

std::string TextFile::getPath() const
{
    return path;
}
