#include <iostream>
#include <chrono>
#include <thread>
#include "Calculator.h"

#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define PURPLE "\033[1;35m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

void findAndReplaceAll(std::string & expression, char toReplace, std::string replaceWith) {
    size_t pos = expression.find(toReplace);
    while( pos != std::string::npos) {
        expression.replace(pos, 1, replaceWith);
        pos = expression.find(toReplace);
    }
}

double calculate(std::string expression, double savedRes) {
    double res;

    findAndReplaceAll(expression, 'X', std::to_string( static_cast<int>(round(savedRes)) ) );


    try {
        res = Calculator::calculate(expression);
    } catch (const std::exception& e) {
        std::cout << RED "Error: " << e.what() << RESET << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return res;
}


int main() {

    std::string expression;
    char inC;
    double res = 0, savedRes = 0;
    bool saved = false;
    int lPar = 0, pPar = 0;

    while (true){
        system("clear");
        std::cout << PURPLE "Options:\n"
                 RED "SIN: " GREEN "sin saved result\n"
                 RED "COS: " GREEN "cos saved result\n"
                 RED "s:" GREEN " save result\n"
                 RED "backspace:" GREEN " erase last character\n"
                 RED "q:" GREEN " quit\n\n"
                 PURPLE "You can also use 'X' as placeholder for saved answer, however it will be rounded to nearest whole number\n"
                 RED "Permitted operators: " GREEN "+ - * / ^ ( )" RESET << std::endl;
        if(saved) {
            std::cout << PURPLE "Saved result: " BLUE << savedRes << RESET << std::endl;
        }
        std::cout << GREEN "Result: " BLUE << res << RESET << std::endl;
        std::cout << GREEN << "Expression: " << PURPLE << expression << std::flush;
        system("/bin/stty raw");
        inC = std::cin.get();
        system("/bin/stty cooked");
        std::cout << RESET << std::flush;

        switch (inC) {
            case 'q':
                return 0;
            case 's':
                saved = true;
                savedRes = res;
                break;
            case 127: // backspace
                if( !expression.empty() )
                expression.pop_back();
                break;
            default:

                expression += inC;

                if(expression == "SIN") {
                    res = sin(savedRes);
                    break;
                }
                else if(expression == "COS") {
                    res = cos(savedRes);
                    break;
                }

                lPar = pPar = 0;

                bool swBreak = false;
                for(auto c : expression) {
                    if(c != 'X' && !std::isdigit(c) && c != '+'
                    && c != '-' && c != '*' && c != '/' && c != '^' && c != '(' && c != ')' ) {
                        swBreak = true;
                        break;
                    }
                    if(c == '(')
                        ++lPar;
                    else if (c == ')')
                        ++pPar;
                }
                if(swBreak || ( ( !std::isdigit(inC) && inC != ')' && inC != 'X' ) || lPar != pPar )) {
                    break;
                }

                res = calculate(expression, savedRes);
                break;
        }
    }
}
