#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "Line.h"

/**
 * @class File
 * @brief Represents a file in an editor
 */
class File {

public:

    explicit File(std::string fileName);

    /**
     * @brief Get the current line
     * @return The current line
     */
    Line & currentLine();

    /**
     * @brief Move the cursor up
     */
    void moveUp();

    /**
     * @brief Move the cursor down
     */
    void moveDown();

    /**
     * @brief Move the cursor left
     */
    void moveLeft();


    /**
     * @brief Move the cursor to the right
     *
     * This function moves the cursor to the right on the current line in the file.
     * If the cursor is at the end of the line, it does nothing.
     */
    void moveRight();


    /**
     * @brief Insert a character at the current cursor position in the file.
     *
     * This function inserts a character at the current cursor position in the file.
     * After insertion, if the file's save state is SAVED, it changes the save state to NOT_SAVED.
     *
     * @param c The character to insert
     */
    void insert(char c);


    /**
     * @brief Inserts a line at the current cursor position in the file.
     *
     * This function inserts a line at the current cursor position in the file.
     *
     * @param line The line to insert
     */
    void insertLine(const Line& line);

    /**
     * @brief Insert a line at the current cursor position
     */
    void insertLine();

    /**
     * @brief Remove the current line
     */
    void removeLine();

    /**
     * @brief Creates new line with the current line's characters after the cursor
     */
    void newLine();

    /**
     * @brief Remove the character before the cursor
     */
    void backspace();

    /**
     * @brief Save the file to disk
     */
    void save();

    /**
     * @brief Print the file to the console
     */
    void print();

    /**
     * @brief Mode of the editor
     */
    enum class Mode {
        NORMAL,
        INSERT
    };

    /**
     * @brief Change the mode of the editor
     * @param mode The new mode
     */
    void changeMode(Mode mode);

    /**
     * @brief Get the current mode of the editor, used only after initialization
     * @return The current mode
     */
    Mode & getMode();

    /**
     * @brief The save state of the file
     */
    enum class saveState {
        DOESNT_EXIST,
        SAVED,
        NOT_SAVED
    };

    /**
     * @brief Get the save state of the file
     * @return The save state
     */
    void setInitialSaveState(saveState state);


private:

    std::string fileName;

    saveState fileSaveState = saveState::DOESNT_EXIST;

    Mode mode = Mode::NORMAL;

    std::vector<Line> lines;

    unsigned int currentLineIndex = 0;

};