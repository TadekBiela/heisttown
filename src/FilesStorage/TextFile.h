#ifndef TEXT_FILE_H
#define TEXT_FILE_H

#include <string>
#include <vector>

using TextFilePath = std::string;
using TextFileContent = std::vector<std::string>;

class TextFile
{
public:
    TextFile() = default;
    TextFile(
        std::string filePath,
        std::string rawFileContent
    );
    virtual ~TextFile() = default;

    auto getPath() const -> TextFilePath;
    auto getContent() const -> TextFileContent;

private:
    TextFilePath path { "" };
    TextFileContent content {};
};

#endif // TEXT_FILE_H
