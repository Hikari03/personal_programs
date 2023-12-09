#include <iostream>
#include <vector>

#include "Grapher.h"

/*
 *| 1|  2|
 *| 4|  8|
 *|16| 32|
 *|64|128|
 */

int main(int argc, char ** argv) {

    Grapher::printGraph(Grapher::graphFunction(argv[1], 10, 10));

    return 0;
}
