#pragma once
#include <vector>
#include <string>

class Line {

public:

    Line() = default;

    Line & operator = (const std::string &line);

    explicit Line(std::string);

    void insert(char c);
    void remove();
    void clear();
    void moveLeft();
    void moveRight();
    unsigned int getCurrentCharacterIndex();
    void setCurrentCharacterIndex(unsigned int index);

    void print(bool selected = false);

    void insertLine(Line &line);
    const std::string & exportLine();

    std::string charsAfterCurrentSelection();

    void removeAfterCurrentSelection();

private:
    std::string characters;

    unsigned int currentCharacterIndex = 0;

};
