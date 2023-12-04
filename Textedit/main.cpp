#include <iostream>
#include <fstream>
#include <string>
#include "File.h"
#include "Macros.h"

/*
 * This program is used to edit text files.
 * It will read in a file and display it to the screen.
 * The user can interact with the text file by using the arrow keys.
 * The user can also use the backspace key to delete characters.
 * The user can also use the enter key to create a new line.
 * The user can also use the escape key to exit the program.
 * */

/**
 * @brief Import a file
 * @param fileName The file to import
 * @return The imported file
 */
File importFile( const std::string & fileName ) {
    File file(fileName);

    std::ifstream inputFile;

    inputFile.open(fileName);

    if(!inputFile.is_open()) {
        file.insertLine(Line(""));
        file.setInitialSaveState(File::saveState::DOESNT_EXIST);
        return file;
    }

    std::string line;

    while(std::getline(inputFile, line)) {
        file.insertLine(Line(line));
    }

    inputFile.close();

    file.setInitialSaveState(File::saveState::SAVED);
    return file;
}

/**
 * @brief Get a character from the console
 * @return The character
 */
int getCharacter() {
    system("/bin/stty raw");
    int c = std::cin.get();
    system("/bin/stty cooked");
    std::cout << RESET << std::flush;
    return c;
}

int main( int argc, char * argv[] ) {

    if(argc < 2 || argc > 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string fileName = argv[1];

    auto file = importFile(fileName);

    File::Mode & mode = file.getMode();


    while(true) {
        file.print();
        int c = getCharacter();

        if constexpr (DEBUG)
            std::cout << GREEN << "\n----------------------\n"
            << " Character: " << c << RESET << std::endl;


        if (c == ESCAPE){
            if constexpr (DEBUG){
                std::cout << GREEN << "Escape key detected" << RESET << std::endl;
            }
            file.print();
            if(getCharacter() == '[')
                switch(getCharacter()) {
                    case 'A': // up arrow key
                        if constexpr(DEBUG)
                            std::cout << GREEN << "Up arrow key detected" << RESET << std::endl;
                        c = UP_ARROW;
                        break;
                    case 'B': // down arrow key
                        if constexpr(DEBUG)
                            std::cout << GREEN << "Down arrow key detected" << RESET << std::endl;
                        c = DOWN_ARROW;
                        break;
                    case 'C': // right arrow key
                        if constexpr(DEBUG)
                            std::cout << GREEN << "Right arrow key detected" << RESET << std::endl;
                        c = RIGHT_ARROW;
                        break;
                    case 'D': // left arrow key
                        if constexpr(DEBUG)
                            std::cout << GREEN << "Left arrow key detected" << RESET << std::endl;
                        c = LEFT_ARROW;
                        break;
                    default:
                        break;
                }
        }

        if(c == CTRL_C)
            break;

        if(mode == File::Mode::INSERT)
            switch (c) {
                case UP_ARROW:
                    file.moveUp();
                    break;
                case DOWN_ARROW:
                    file.moveDown();
                    break;
                case RIGHT_ARROW:
                    file.moveRight();
                    break;
                case LEFT_ARROW:
                    file.moveLeft();
                    break;
                case '`':
                    file.changeMode(File::Mode::NORMAL);
                    continue;
                case BACKSPACE:
                    file.backspace();
                    break;
                case ENTER:
                    file.newLine();
                    break;
                default:
                    file.insert(static_cast<char>(c));
                    break;
            }

        if(mode == File::Mode::NORMAL)
            switch (c) {
                case UP_ARROW:
                    file.moveUp();
                    break;
                case DOWN_ARROW:
                    file.moveDown();
                    break;
                case RIGHT_ARROW:
                    file.moveRight();
                    break;
                case LEFT_ARROW:
                    file.moveLeft();
                    break;
                case 'i':
                    file.changeMode(File::Mode::INSERT);
                    break;
                case 'w':
                    file.save();
                    break;
                case 'q':
                    std::cout << BG_RED << "\nAre you sure you want to quit? (y/N)" << RESET << std::endl;
                    char c;
                    c = getCharacter();
                    if(c == 'y' || c == 'Y')
                        return 0;
                    continue;
                case 'd':
                    file.removeLine();
                    break;
                default:
                    break;
            }

        if constexpr (DEBUG)
            std::cout << GREEN << "----------------------" << RESET << std::endl;
    }
}

