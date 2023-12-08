#pragma once
#include <vector>
#include <string>


/**
 * @brief Graphs in braille
 *
 * Responsible for graphing the input function in braille.
 * The input function is a linear function of the form f(x) = q*x + c.
 * This class is responsible for calculating the dots for each permutation of the braille alphabet.
 */
class Grapher {

public:
    Grapher() = default;

private:

    std::vector<std::vector<std::string>> graph;
};