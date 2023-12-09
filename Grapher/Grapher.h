#pragma once
#include <vector>
#include <string>
#include <cmath>

#include "DotsPermutations.h"
#include "Calculator.h"

/**
 * @brief Graphs in braille
 *
 * Responsible for graphing the input function in braille.
 * This class is responsible for calculating the dots for each permutation of the braille alphabet.
 * And then it uses the dots to generate the graph.
 */
class Grapher {

public:
    Grapher() = default;

    /**
     * @brief Graphs the input function in braille
     *
     * @param input The input function
     * @return The graph
     */
    static std::vector<std::vector<std::string>> graphFunction(const std::string & input, int width, int height);

    static void printGraph(const std::vector<std::vector<std::string>> & graph);

private:

    /**
     * @brief Calculates index of left dot in braille alphabet
     * @param number
     * @return index of left dot, f.e. "⠂" is 4 and represents number 3
     */
    [[nodiscard]] static int get1stDot(int number) ;

    /**
     * @brief Calculates index of right dot in braille alphabet
     * @param number
     * @return index of right dot, f.e. "⠐" is 8 and represents number 3
     */
    [[nodiscard]] static int get2ndDot(int number) ;

    /**
     * @brief Finds and replaces all occurrences of a character in a string
     *
     * @param expression The string to search in
     * @param toReplace The character to replace
     * @param replaceWith The string to replace with
     */
    static std::string findAndReplaceAll(const std::string & expression, char toReplace, const std::string& replaceWith);

    static int calculateForX(const std::string & input, int x);

    static std::pair<int, int> getDotIdxAndLayerForX(const std::string & input, int x, bool isFor2ndDot);

};