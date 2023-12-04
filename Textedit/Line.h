#pragma once
#include <vector>
#include <string>
#include "Macros.h"

class Line {

public:

    Line() = default;

    Line & operator = (const std::string &line);

    explicit Line(std::string);

    /**
     * @brief Insert a character at the current cursor position
     * @param c
     */
    void insert(char c);

    /**
     * @brief Remove the character before the cursor
     */
    void remove();

    /**
     * @brief Clears the whole line
     */
    void clear();

    /**
     * @brief Move the cursor left
     */
    void moveLeft();

    /**
     * @brief Move the cursor right
     */
    void moveRight();

    /**
     * @brief Get the current cursor position
     * @return The current cursor position
     */
    unsigned int getCurrentCharacterIndex();

    /**
     * @brief Set the current cursor position
     * @param index The new cursor position
     */
    void setCurrentCharacterIndex(unsigned int index);

    /**
     * @brief Print the line
     * @param selected Whether the line is selected or not
     */
    void print(bool selected = false);

    /**
     * @brief Concatenate two lines
     * @param line
     */
    void insertLine(Line &line);

    /**
     * @brief Get the line's characters
     * @return The line's characters
     */
    const std::string & exportLine();

    /**
     * @brief Get the characters after the current selection
     * @return The characters after the current selection
     */
    std::string charsAfterCurrentSelection();

    /**
     * @brief Remove the characters after the current selection
     */
    void removeAfterCurrentSelection();

private:
    std::string characters;

    unsigned int currentCharacterIndex = 0;

};
