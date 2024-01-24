#pragma once

#include "Tile.h"

/**
 * @brief Extends Tile class with color support
 */
class ColorTile : public Tile {

public:
    ColorTile();
    ColorTile(const ColorTile & other) = default;

    void setColor(int color);

    [[nodiscard]] int getColor() const;

    void print(unsigned x, unsigned y) const override;

private:
    int color = 0;
};