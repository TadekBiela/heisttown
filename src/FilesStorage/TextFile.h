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
    TextFile(std::string filePath);
    TextFile(
        std::string filePath,
        const std::string& rawFileContent
    );
    virtual ~TextFile() = default;

    auto getPath() const -> TextFilePath;
    auto getContent() const -> const TextFileContent&;

private:
    TextFilePath path { "" };
    TextFileContent content {};

    auto getRawFileContent() const -> std::string;
    void loadContent(const std::string& rawFileContent);
};

#endif // TEXT_FILE_H
