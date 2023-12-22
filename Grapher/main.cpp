#include <iostream>
#include <vector>

#include "Grapher.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define PURPLE "\033[0;35m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"

/*
 *| 1|  2|
 *| 4|  8|
 *|16| 32|
 *|64|128|
 */

void interactiveMode(const int width, const int height) {
    std::string expression;
    char inC;
    int lPar = 0, pPar = 0;

    bool firstRun = true;

    Graph graph(1,1,1,1);

    while (true){
        system("clear");
        std::cout << PURPLE "Options:\n"
                 RED "backspace:" GREEN " erase last character\n"
                 RED "q:" GREEN " quit\n\n"
                 RED "Permitted operators: " GREEN "+ - * / ^ ( )" RESET << std::endl;

        std::cout << GREEN << "Expression: " << PURPLE << expression << std::flush;
        std::cout << GREEN << "\nResult: \n" << PURPLE;

        if (!firstRun)
            graph.printGraph();
        else firstRun = false;

        std::cout.flush();

        system("/bin/stty raw");
        inC = std::cin.get();
        system("/bin/stty cooked");
        std::cout << RESET << std::flush;

        switch (inC) {
            case 'q':
                return;
            case 127:
                if( !expression.empty() )
                    expression.pop_back();
            break;
            default:

                expression += inC;


            lPar = pPar = 0;

            bool swBreak = false;
            for(auto c : expression) {
                if(c != 'x' && !std::isdigit(c) && c != '+'
                && c != '-' && c != '*' && c != '/' && c != '^' && c != '(' && c != ')' ) {
                    swBreak = true;
                    break;
                }
                if(c == '(')
                    ++lPar;
                else if (c == ')')
                    ++pPar;
            }
            if(swBreak || ( ( !std::isdigit(inC) && inC != ')' && inC != 'x' ) || lPar != pPar )) {
                break;
            }

            graph = Grapher::graphFunction(expression, width, height);

            break;
        }
    }
}

int main(int argc, char ** argv) {

    std::string const argv1 = argv[1];

    if(argv1 == "-h" || argv1 == "--help" || argv1.empty()) {
        std::cout << GREEN "Modes: \n"
                     GREEN "    -i:" PURPLE " interactive mode\n"
                     PURPLE"        Usage: " BLUE << argv[0] << " -i <width> <height>\n"
                     GREEN "    -c:" PURPLE " command line mode\n"
                     PURPLE"        Usage: " BLUE << argv[0] << " -c <width> <height> <expression>\n" RESET << std::endl;

        return 1;
    }

    if(argv1 == "-i") {
        if(argc != 4) {
            std::cout << "Usage: " << argv[0] << " -i <width> <height>" << std::endl;
            return 1;
        }

        interactiveMode(std::stoi(argv[2]), std::stoi(argv[3]));
    }

    if(argv1 == "-c") {
        if(argc != 5) {
            std::cout << "Usage: " << argv[0] << " -c <width> <height> <expression>" << std::endl;
            return 1;
        }

        Grapher::graphFunction(argv[4], std::stoi(argv[2]), std::stoi(argv[3])).printGraph();

    }


    return 0;
}
