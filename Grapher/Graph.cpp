#include "Graph.h"

Graph::Graph(const int height, const int width, const double xScale, const double yScale):
                    data(height, std::vector<std::string>(width, " ")),
                    xScale(xScale), yScale(yScale), height(height), width(width) {}

Graph & Graph::operator=(const Graph& other) {
    if(this == &other) {
        return *this;
    }

    data = other.data;
    xScale = other.xScale;
    yScale = other.yScale;
    height = other.height;
    width = other.width;

    return *this;
}

void Graph::insertDot(const int y, const int x, const std::string & dot) {

    if(x<0 || x>width || y<0 || y>height) {
        throw std::invalid_argument("x or y out of bounds");
    }

    data[y][x] = dot;
}

void Graph::printGraph() const {
    for(int i = static_cast<int>(data.size())-1; i >= 0; --i) {
        std::cout << i*4*static_cast<int>(yScale) << "_";
        auto const legend = std::to_string(i*4*static_cast<int>(yScale));
        for(int j = 0; j < 5-legend.size(); ++j) {
            std::cout << " ";
        }

        std::cout << "|";

        for(const auto & dot : data[i]) {
            std::cout << dot;
        }
        std::cout << std::endl;
    }

}
