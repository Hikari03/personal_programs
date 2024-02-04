#pragma once

#include <vector>
#include <memory>
#include <optional>
#include <stdexcept>
#include "Tile.h"
#include "ColorTile.h"

/**
 * @brief Holds and manages tiles matrix
 */
class Tiles {
public:

    Tiles(unsigned width_, unsigned height_);

    void resize(unsigned width_, unsigned height_);

    void insertTile(unsigned x, unsigned y, wchar_t c = L' ');

    std::shared_ptr<Tile> getTile(unsigned x, unsigned y);

    std::shared_ptr<Tile> & setColor(unsigned x, unsigned y, int color);

    void clear();

    friend class Renderer;

private:
    std::vector<std::vector<std::shared_ptr<Tile>>> tiles;

    unsigned int width = 0;
    unsigned int height = 0;
};