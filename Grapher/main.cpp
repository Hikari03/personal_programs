#include <cmath>
#include <iostream>
#include <vector>

#include "DotsPermutations.h"

/**
 * @brief Parses the input string and returns the quotient of x and constant
 */
std::pair<int, int> inputParser(const std::vector<std::string> & input) {

    int qOfX = input[0].at(0) - '0';

    if(qOfX == 'x' - '0') {
        qOfX = 1;
    }

    int constant = input[2].at(0) - '0';
    constant *= input[2].at(0) == '-' ? -1 : 1;

    return {qOfX, constant};
}

/*int findAllPowersOfTwo(const int number) {
    int sum = 0;
    for (int i = 0; i < 6; ++i) {
        if (number & (1 << i)) {
            sum += i+1;
        }
    }
    return sum;
}*/

/*
 *| 1|  2|
 *| 4|  8|
 *|16| 32|
 *|64|128|
 */

int main() {
    //std::cout << dots.at(2+4+32+64) << std::endl;

    std::vector<std::string> input = { {"x"}, {"+"}, {"1"} };


    auto [qOfX, constant] = inputParser(input);

    int layer = 1;
    for (int i = 0; i < 1; i+=2) {
        if (i*qOfX + constant > 0) {
            int res = 0;
            int tmp = i*qOfX + constant;

            if(tmp <= layer*4 && tmp > (layer-1)*4) {
                tmp = tmp - (layer-1)*4;
                res = std::pow(2, (4-tmp)*2 );
            }

            tmp = (i+1)*qOfX + constant;
            if(tmp <= layer*4 && tmp > (layer-1)*4) {
                tmp = tmp - (layer-1)*4;
                res += std::pow(2, ((4-tmp)*2)+1 );
            }

            std::cout << (res == 0 ? " " : dots.at(res)) << std::flush;
        }
    }


    return 0;
}
