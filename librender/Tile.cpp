#include <iostream>
#include "Tile.h"

using namespace std;


void Tile::setChar(wchar_t c) {
    ch = c;
}

const wchar_t & Tile::getChar() const {
    return ch;
}

void Tile::print(unsigned x, unsigned y) const {
    mvprintw(static_cast<int>(x), static_cast<int>(y), "%lc", ch);
}

Tile::Type Tile::getType() const {
    return tileType;
}
