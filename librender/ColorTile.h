#pragma once

#include "Tile.h"

/**
 * @brief Extends Tile class with color support
 */
class ColorTile : public Tile {

public:
    ColorTile() = default;
    ColorTile(const ColorTile & other) = default;

    void setColor(int color);

    [[nodiscard]] int getColor() const;

    void print(int x, int y) const override;

private:
    int color = 0;
};