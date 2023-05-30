#ifndef TEXT_FILE_H
#define TEXT_FILE_H

#include <string>

class TextFile
{
public:
    TextFile() = default;
    TextFile(std::string filepath, std::string filecontent);
    virtual ~TextFile();

    std::string getPath() const;
    std::string getContent() const;

private:
    std::string path;
    std::string content;
};

#endif //TEXT_FILE_H
