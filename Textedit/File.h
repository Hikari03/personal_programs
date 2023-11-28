#pragma once

#include "Line.h"

class File {

public:

    explicit File(std::string fileName);
    Line & currentLine();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void insert(char c);
    void insertLine(const Line& line);
    void remove();
    void newLine();
    void backspace();

    // print the file to the screen
    void print();

    enum class Mode {
        NORMAL,
        INSERT
    };

    void changeMode(Mode mode);
    Mode & getMode();


private:

    std::string fileName;


    Mode mode = Mode::NORMAL;

    std::vector<Line> lines;

    unsigned int currentLineIndex = 0;

};