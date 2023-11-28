#include <iostream>
#include <fstream>
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

File importFile( const std::string & fileName ) {
    File file(fileName);

    std::ifstream inputFile(fileName);

    std::string line;

    while(std::getline(inputFile, line)) {
        file.insertLine(Line(line));
    }

    inputFile.close();

    return file;
}

int getCharacter() {
    system("/bin/stty raw");
    int c = std::cin.get();
    system("/bin/stty cooked");
    return c;
}

int main( int argc, char * argv[] ) {

    if(argc < 2 || argc > 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string fileName = argv[1];

    File file = importFile(fileName);

    File::Mode & mode = file.getMode();

    file.print();

    while(true) {
        int c = getCharacter();

        if constexpr (DEBUG)
            std::cout << GREEN << "----------------------\n"
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

        switch(c) {
            case TAB: // escape key
                return 0;
            case BACKSPACE: // backspace key
                file.backspace();
                break;
            case ENTER: // enter key
                file.newLine();
                break;
            case UP_ARROW: // up arrow key
                file.moveUp();
                break;
            case DOWN_ARROW: // down arrow key
                file.moveDown();
                break;
            case RIGHT_ARROW: // right arrow key
                file.moveRight();
                break;
            case LEFT_ARROW: // left arrow key
                file.moveLeft();
                break;
            default:
                if(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
                    file.insert(static_cast<char>(c));
                break;
        }

        if constexpr (DEBUG)
            std::cout << GREEN << "----------------------" << RESET << std::endl;

        file.print();
    }
}

