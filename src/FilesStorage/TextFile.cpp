#include "TextFile.hpp"
#include <algorithm>
#include <exception>
#include <fstream>
#include <iterator>
#include <sstream>

TextFile::TextFile(std::string filePath)
    : path(std::move(filePath))
{
    loadContent(getRawFileContent());
}

TextFile::TextFile(
    std::string filePath,
    const std::string& rawFileContent
)
    : path(std::move(filePath))
{
    loadContent(rawFileContent);
}

auto TextFile::getRawFileContent() const -> std::string
{
    std::ifstream fileStream(path);

    if (fileStream.is_open())
    {
        std::stringstream buffer;
        buffer << fileStream.rdbuf();
        fileStream.close();
        return buffer.str();
    }

    std::string exceptionMsg { "File " + path + " doesn't exist or file path is wrong." };
    throw std::runtime_error(exceptionMsg.c_str());
}

void TextFile::loadContent(const std::string& rawFileContent)
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

auto TextFile::getContent() const -> const TextFileContent&
{
    return content;
}
