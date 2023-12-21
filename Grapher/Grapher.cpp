#include "Grapher.h"

std::string Grapher::findAndReplaceAll(const std::string & expression, char toReplace, const std::string &replaceWith) {
    std::string expressionCopy = expression;
    size_t pos = expressionCopy.find(toReplace);
    while( pos != std::string::npos) {
        expressionCopy.replace(pos, 1, replaceWith);
        pos = expressionCopy.find(toReplace);
    }
    return expressionCopy;
}

int Grapher::get1stDot(const int number) {
    if(number == 0 || number > 4) {
        return 0;
    }
    return static_cast<int>(std::pow(2, (4-number)*2 ));
}

int Grapher::get2ndDot(const int number) {
    if(number == 0 || number > 4) {
        return 0;
    }
    return static_cast<int>(std::pow(2, ((4-number)*2)+1 ));
}

Graph Grapher::graphFunction(const std::string & input, const int width, const int height) {

    auto const calcWidth = width % 2 == 0 ? width : width-1;

    Graph graph(height, width, 1, 1);


    for(int i = 0, idx = 0; i < calcWidth; i+=2, ++idx) {

        auto [dot1, layer1] = getDotIdxAndLayerForX(input, i, false);

        auto [dot2, layer2] = getDotIdxAndLayerForX(input, i+1, true);

        // Check if layer is < 0, because we only graph 1st quadrant
        if(layer1 < 0 || layer2 < 0) {
            continue;
        }

        if(layer1 == layer2) {
            if(layer1 > height-1) {
                continue;
            }
            graph.insertDot(layer1, idx, dots.at(dot1+dot2));
        } else {
            if(layer1 > height-1 || layer2 > height-1) {
                continue;
            }

            graph.insertDot(layer1, idx, dots.at(dot1));
            graph.insertDot(layer2, idx, dots.at(dot2));
        }
    }

    return graph;
}


double Grapher::calculateForX(const std::string &input, const int x) {
    auto const inputString = findAndReplaceAll(input, 'x', std::to_string(x));

    return Calculator::calculate(inputString);
}

std::pair<int, int> Grapher::getDotIdxAndLayerForX(const std::string &input, const int x, bool isFor2ndDot) {

    if constexpr (DEBUG) {
        std::cout << "Calculating for x: " << x << std::endl;
    }
    auto const calculated = calculateForX(input, x)+1;

    if constexpr (DEBUG) {
        std::cout << "Calculated: " << calculated << std::endl;
    }

    int layer = std::abs(static_cast<int>(calculated))/4;
    if(static_cast<int>(calculated) % 4 == 0 && layer != 0) {
        --layer;
    }

    if(calculated < 0)
        layer = -layer;

    int dotIdx = 0;

    if(calculated>=0)
        dotIdx = isFor2ndDot ? get2ndDot(calculated - layer*4) : get1stDot(calculated - layer*4);

    return {dotIdx, layer};
}
