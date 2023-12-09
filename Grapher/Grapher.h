#pragma once
#include <vector>
#include <string>
#include <cmath>


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

    /**
     * @brief Calculates index of left dot in braille alphabet
     * @param number
     * @return index of left dot, f.e. "⠂" is 4 and represents number 3
     */
    [[nodiscard]] int get1stDot(int number) const;

    /**
     * @brief Calculates index of right dot in braille alphabet
     * @param number
     * @return index of right dot, f.e. "⠐" is 8 and represents number 3
     */
    [[nodiscard]] int get2ndDot(int number) const;

    /**
     * @brief Finds and replaces all occurrences of a character in a string
     *
     * @param expression The string to search in
     * @param toReplace The character to replace
     * @param replaceWith The string to replace with
     */
    static void findAndReplaceAll(std::string & expression, char toReplace, const std::string& replaceWith);

    std::vector<std::vector<std::string>> graph;

};