#pragma once

#include <vector>
#include <map>
#include "Tile.h"
#include "ColorTile.h"
#include "Tiles.h"

/**
 * @brief Used for rendering
 * @details Makes use of ncurses library to render Tiles\n
 *          Print function can be extended to support more than just Tiles\n
 *          Then, call init() to initialize the renderer
 */
class Renderer {
public:
    explicit Renderer(Tiles & tiles_);
    ~Renderer();

    void print();

    [[nodiscard]] short initColor(short foreground, short background, std::optional<short> index = std::nullopt);

private:

    void copyTiles();

    std::vector<std::vector<std::shared_ptr<Tile>>> & tiles;
    std::vector<std::vector<std::shared_ptr<Tile>>> prevTiles;

            //index         foreground, background
    std::map<short, std::pair<short, short>> colorPairs;

    unsigned int width = 0;
    unsigned int height = 0;
};