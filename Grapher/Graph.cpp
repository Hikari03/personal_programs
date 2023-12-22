#include "Graph.h"

Graph::Graph(const int absHeight, const int width, const double xScale, const double yScale):
                    data(absHeight*2-1, std::vector<std::string>(width, " ")),
                    xScale(xScale), yScale(yScale),absHeight(absHeight), height(absHeight*2-1), width(width) {}

Graph & Graph::operator=(const Graph& other) {
    if(this == &other) {
        return *this;
    }

    data = other.data;
    xScale = other.xScale;
    yScale = other.yScale;
    height = other.height;
    absHeight = other.absHeight;
    width = other.width;

    return *this;
}

void Graph::insertDot(const int y, const int x, const std::string & dot) {

    if(x<0 || x>width || y<absHeight-height || y>absHeight) {
        throw std::invalid_argument("x or y out of bounds");
    }

    if constexpr (false) {
        std::cout << "insertDot: y=" << y << std::endl;
    }

    data[y+absHeight-1][x] = dot;
}

void Graph::printGraph() const {
    for(int i = absHeight-1; i >= absHeight-height+1; --i) {
        std::cout << i*4*static_cast<int>(yScale) << "_";
        auto const legend = std::to_string(i*4*static_cast<int>(yScale));
        for(int j = 0; j < 5-legend.size(); ++j) {
            std::cout << " ";
        }

        std::cout << "|";

        for(const auto & dot : data[i+absHeight-1]) {
            std::cout << dot;
        }
        std::cout << std::endl;
    }

}
