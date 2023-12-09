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

std::vector<std::vector<std::string>>
Grapher::graphFunction(const std::string & input, const int width, const int height) {

    std::vector<std::vector<std::string>> graph(height, std::vector<std::string>(width, " "));

    auto calcWidth = width % 2 == 0 ? width : width-1;

    for(int i = 0, idx = 0; i < calcWidth; i+=2, ++idx) {

        auto [dot1, layer1] = getDotIdxAndLayerForX(input, i, false);

        auto [dot2, layer2] = getDotIdxAndLayerForX(input, i+1, true);

        if(layer1 == layer2) {
            if(layer1 > height-1) {
                continue;
            }
            graph[layer1][idx] = dots.at(dot1+dot2);
        } else {
            if(layer1 > height-1 || layer2 > height-1) {
                continue;
            }

            graph[layer1][idx] = dots.at(dot1);
            graph[layer2][idx] = dots.at(dot2);
        }
    }

    return graph;
}

void Grapher::printGraph(const std::vector<std::vector<std::string>> &graph) {
    for(int i = graph.size()-1; i >= 0; --i) {
        for(const auto & dot : graph[i]) {
            std::cout << dot;
        }
        std::cout << std::endl;
    }

}

int Grapher::calculateForX(const std::string &input, const int x) {
    auto inputString = findAndReplaceAll(input, 'x', std::to_string(x));

    return static_cast<int>(Calculator::calculate(inputString));
}

std::pair<int, int> Grapher::getDotIdxAndLayerForX(const std::string &input, int x, bool isFor2ndDot) {
    auto calculated = calculateForX(input, x);
    int layer = calculated/4;
    if(calculated % 4 == 0 && layer != 0) {
        --layer;
    }
    int dotIdx = isFor2ndDot ? get2ndDot(calculated - layer*4) : get1stDot(calculated - layer*4);

    return {dotIdx, layer};
}
