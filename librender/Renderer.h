#pragma once

#include <vector>
#include "Tile.h"

/**
 * @brief Used for rendering
 * @details Makes use of ncurses library to render Tiles\n
 *          Print function can be extended to support more than just Tiles\n
 *          Then, call init() to initialize the renderer
 */
class Renderer {
public:
    explicit Renderer(std::vector<std::vector<std::shared_ptr<Tile>>> & tiles, unsigned width_, unsigned height_);

    void print();

private:

    void copyTiles();

    std::vector<std::vector<std::shared_ptr<Tile>>> & tiles;
    std::vector<std::vector<std::shared_ptr<Tile>>> prevTiles;

    unsigned int width = 0;
    unsigned int height = 0;
};