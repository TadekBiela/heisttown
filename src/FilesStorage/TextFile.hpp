#pragma once

#include <string>
#include <vector>

using TextFilePath = std::string;
using TextFileContent = std::vector<std::string>;

class TextFile
{
public:
    TextFile() = default;
    explicit TextFile(std::string filePath);
    TextFile(
        std::string filePath,
        const std::string& rawFileContent
    );
    virtual ~TextFile() = default;

    [[nodiscard]] TextFilePath getPath() const;
    [[nodiscard]] const TextFileContent& getContent() const;

private:
    TextFilePath path;
    TextFileContent content;

    [[nodiscard]] std::string getRawFileContent() const;
    void loadContent(const std::string& rawFileContent);
};
