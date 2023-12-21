#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

class Graph {
public:
    Graph(int height, int width , double xScale, double yScale);

    Graph & operator = (const Graph & other);

    void insertDot(int y, int x, const std::string & dot);

    void printGraph() const;

    std::vector<std::vector<std::string>> data;

private:
    double xScale = 1;
    double yScale = 1;

    int height = 0;
    int width = 0;


};
