#ifndef TEXT_FILE_H
#define TEXT_FILE_H

#include <string>

class TextFile
{
public:
    TextFile() = default;
    TextFile(std::string filepath, std::string filecontent);
    virtual ~TextFile();

    std::string getContent() const;
    std::string getPath() const;

private:
    std::string content;
    std::string path;
};

#endif //TEXT_FILE_H
