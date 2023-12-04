#include <climits>
#include <iostream>
#include <fstream>
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
    if(fileSaveState == File::saveState::SAVED)
        fileSaveState = File::saveState::NOT_SAVED;
}

void File::insertLine(const Line& line) {
    lines.push_back(line);
}

void File::insertLine() {
    lines.insert(lines.begin() + currentLineIndex + 1, Line());
    ++currentLineIndex;
}

void File::removeLine() {
    if(lines.size() > 1) {
        lines.erase(lines.begin() + currentLineIndex);
        if(currentLineIndex > 0)
            --currentLineIndex;
    }
    else {
        lines.at(0).clear();
    }
    if(fileSaveState == File::saveState::SAVED)
        fileSaveState = File::saveState::NOT_SAVED;
}

void File::newLine() {
    Line newLine;

    if(currentLineIndex < lines.size()) {
        newLine = currentLine().charsAfterCurrentSelection();
        currentLine().removeAfterCurrentSelection();
    }

    lines.insert(lines.begin() + currentLineIndex + 1, newLine);
    ++currentLineIndex;
    if(fileSaveState == File::saveState::SAVED)
        fileSaveState = File::saveState::NOT_SAVED;
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
    if(fileSaveState == File::saveState::SAVED)
        fileSaveState = File::saveState::NOT_SAVED;
}

void File::print() {

    if constexpr (!DEBUG)
        std::cout << CLEAR << std::flush;

    std::cout << WHITE << "File: " << fileName << RESET << std::endl;
    auto const w(WEXITSTATUS(std::system("exit `tput cols`")));

    std::cout << WHITE << "Line: " << currentLineIndex + 1 << "/" << lines.size() << RESET << std::endl;
    std::cout << WHITE;
    for(int i = 0; i < w; i++)
        std::cout << "━";
    std::cout << RESET << std::endl;

    for(auto & line : lines) {
        if(&line == &currentLine())
            line.print(true);
        else
            line.print();
    }

    std::cout << WHITE;
    for(int i = 0; i < w; i++)
        std::cout << "━";
    std::cout << RESET << std::endl;

    std::cout << WHITE << "Mode: " << (mode == Mode::NORMAL ? "NORMAL" : "INSERT") << RESET;
    std::cout << (fileSaveState == File::saveState::SAVED ? GREEN : fileSaveState == File::saveState::NOT_SAVED ? BLUE : RED) << " | " << MAGENTA << std::flush;
}

void File::changeMode(File::Mode mode) {
    this->mode = mode;
}

File::Mode & File::getMode() {
    return mode;
}

void File::save() {
    std::ofstream file;
    file.open(fileName, std::ios::out);

    if(!file.is_open()) {
        std::cout << RED << "\nError opening file, would you like to create new one? (Y/n)" << std::endl;
        char c;
        c = std::cin.get();
        if(c == 'n' || c == 'N')
            return;
        else {
            file.open(fileName, std::ios::out);
            if(!file.is_open()) {
                std::cout << RED << "\nError creating file" << std::endl;
                return;
            }
        }
    }

    for(auto & line : lines) {
        file << line.exportLine() << std::endl;
    }

    file.close();
    fileSaveState = File::saveState::SAVED;
}

void File::setInitialSaveState(File::saveState state) {
    fileSaveState = state;
}