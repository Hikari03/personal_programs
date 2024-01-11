#include <iostream>
#include <utility>
#include "Line.h"


Line::Line(std::string line) : characters(std::move(line)) {}

void Line::insert(char c) {

    characters.insert(characters.begin() + currentCharacterIndex, c);
    currentCharacterIndex++;
}

void Line::remove() {

    if(currentCharacterIndex > 0) {
        characters.erase(characters.begin() + currentCharacterIndex - 1);
        currentCharacterIndex--;
    }
}

void Line::moveLeft() {

    if(currentCharacterIndex > 0) {
        currentCharacterIndex--;
    }
}

void Line::moveRight() {

    if(currentCharacterIndex < characters.size()) {
        currentCharacterIndex++;
    }
}

unsigned int Line::getCurrentCharacterIndex() const {
    return currentCharacterIndex;
}

void Line::print(bool selected) {

    for(auto & character : characters) {

        // if character is selected, print it with a different color
        // else print it normally

        if(selected && currentCharacterIndex == &character - &characters[0]) {
            std::cout << BG_WHITE << character << RESET;
        }
        else
            std::cout << character;
    }

    if(selected && currentCharacterIndex == characters.size())
        std::cout << BG_WHITE << " " << RESET;
    else
        std::cout << " ";

    std::cout << std::endl;
}

void Line::insertLine(Line & line) {
    characters += line.characters;
}

std::string Line::charsAfterCurrentSelection() {
    return characters.substr(currentCharacterIndex);
}

Line & Line::operator = (const std::string & line) {
    characters = line;
    return *this;
}

void Line::removeAfterCurrentSelection() {
    characters.erase(currentCharacterIndex);
}

void Line::setCurrentCharacterIndex(unsigned int index) {

    if(index <= characters.size())
        currentCharacterIndex = index;
    else
        currentCharacterIndex = characters.size();
}

const std::string & Line::exportLine() {
    return characters;
}

void Line::clear() {
    characters.clear();
    currentCharacterIndex = 0;
}
