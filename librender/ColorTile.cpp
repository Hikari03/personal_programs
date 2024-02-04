#include "ColorTile.h"

void ColorTile::setColor(int color_) {
    this->color = color_;
    _updated = true;
}

void ColorTile::print(unsigned x, unsigned y) {
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
