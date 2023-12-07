#include "TextFile.h"
#include <algorithm>
#include <iterator>

TextFile::TextFile(std::string filePath,
    std::string rawFileContent
)
    : path(std::move(filePath))
{
    auto beginLinePos = std::begin(rawFileContent);
    auto endLinePos = beginLinePos;
    do
    {
        endLinePos = std::find(beginLinePos, std::end(rawFileContent), '\n');
        auto lineLength = std::distance(beginLinePos, endLinePos);
        auto lineBeginPos = std::distance(std::begin(rawFileContent), beginLinePos);
        std::string line = rawFileContent.substr(lineBeginPos, lineLength);
        if (!line.empty())
        {
            content.push_back(line);
        }
        beginLinePos = endLinePos + 1;
    } while (endLinePos != std::end(rawFileContent));
}

auto TextFile::getPath() const -> TextFilePath
{
    return path;
}

auto TextFile::getContent() const -> TextFileContent
{
    return content;
}
