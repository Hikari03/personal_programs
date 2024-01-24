#include "ColorTile.h"

void ColorTile::setColor(int color_) {
    this->color = color_;
}

void ColorTile::print(unsigned x, unsigned y) const {
    attron(COLOR_PAIR(color));
    Tile::print(x, y);
    attroff(COLOR_PAIR(color));
}

int ColorTile::getColor() const {
    return color;
}

ColorTile::ColorTile() {
    tileType = Tile::Type::ColorTile;
}
