#include <climits>
#include <iostream>
#include "File.h"
#include "Macros.h"

File::File(std::string fileName) : fileName(std::move(fileName)) {}

Line & File::currentLine() {
    return lines[currentLineIndex];
}

void File::moveUp() {
    if(currentLineIndex > 0) {
        unsigned int idx = currentLine().getCurrentCharacterIndex();
        currentLineIndex--;
        currentLine().setCurrentCharacterIndex(idx);
    }
}

void File::moveDown() {
    if(currentLineIndex < lines.size() - 1) {
        unsigned int idx = currentLine().getCurrentCharacterIndex();
        currentLineIndex++;
        currentLine().setCurrentCharacterIndex(idx);
    }
}

void File::moveLeft() {
    currentLine().moveLeft();
}

void File::moveRight() {
    currentLine().moveRight();
}

void File::insert(char c) {
    currentLine().insert(c);
}

void File::insertLine(const Line& line) {
    lines.push_back(line);
}

void File::remove() {
    currentLine().remove();
}

void File::newLine() {
    Line newLine;

    if(currentLineIndex < lines.size() - 1) {
        newLine = currentLine().charsAfterCurrentSelection();
        currentLine().removeAfterCurrentSelection();
    }

    lines.insert(lines.begin() + currentLineIndex + 1, newLine);
    ++currentLineIndex;
}

void File::backspace() {
    if(currentLine().getCurrentCharacterIndex() == 0) {
        if(currentLineIndex > 0) {
            lines.at(currentLineIndex-1).insertLine(currentLine());
            currentLineIndex--;
            lines.erase(lines.begin() + currentLineIndex + 1);
            currentLine().setCurrentCharacterIndex(INT_MAX);
        }
    } else {
        currentLine().remove();
    }
}

void File::print() {

    if constexpr (!DEBUG)
        std::cout << CLEAR << std::flush;

    for(auto & line : lines) {
        if(&line == &currentLine())
            line.print(true);
        else
            line.print();
    }
}

void File::changeMode(File::Mode mode) {
    this->mode = mode;
}

File::Mode & File::getMode() {
    return & mode;
}