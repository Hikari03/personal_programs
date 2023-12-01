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
    void insertLine();
    void removeLine();
    void newLine();
    void backspace();

    void save();

    // print the file to the screen
    void print();

    enum class Mode {
        NORMAL,
        INSERT
    };

    void changeMode(Mode mode);
    Mode & getMode();

    enum class saveState {
        DOESNT_EXIST,
        SAVED,
        NOT_SAVED
    };

    void setInitialSaveState(saveState state);


private:

    std::string fileName;

    saveState fileSaveState = saveState::DOESNT_EXIST;

    Mode mode = Mode::NORMAL;

    std::vector<Line> lines;

    unsigned int currentLineIndex = 0;

};