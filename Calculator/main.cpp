#include <iostream>
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


int main() {
    std::cout << PURPLE "Options:\n"
                 RED "sin: " GREEN "sin previous result\n"
                 RED "cos: " GREEN "cos previous result\n"
                 RED "e:" GREEN " exit\n\n"
                 PURPLE "You can also use 'X' as placeholder for previous answer, however it will be rounded to nearest whole number\n"
                 RED "Permitted operators: " GREEN "+ - * / ^ ( )" RESET << std::endl;

    std::string expression;
    double res = 0;

    while(expression != "e"){
        std::cout << PURPLE "Enter expression: " RESET BLUE;
        getline(std::cin, expression);
        std::cout << RESET << std::flush;

        if(expression == "sin") {
            std::cout << GREEN "Calculating: " BLUE "sin("  + std::to_string(res) + ')' + RESET << std::endl;
            res = sin(res);
        }
        else if(expression == "cos") {
            std::cout << GREEN "Calculating: " BLUE "cos("  + std::to_string(res) + ')' + RESET << std::endl;
            res = cos(res);
        }
        else if(expression == "e") {
            continue;
        }
        else {

            findAndReplaceAll(expression, 'X', std::to_string( static_cast<int>(round(res)) ) );

            std::cout << GREEN "Calculating: " BLUE + expression + RESET << std::endl;

            try {
                res = Calculator::calculate(expression);
            } catch (const std::exception& e) {
                std::cout << RED "Error: " << e.what() << RESET << std::endl;
                return 1;
            }
        }

        std::cout << GREEN "Result: " BLUE << res << RESET << std::endl;
    }







    return 0;
}
