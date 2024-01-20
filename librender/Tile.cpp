#include <iostream>
#include "Tile.h"

using namespace std;


void Tile::setChar(wchar_t c) {
    ch = c;
}

const wchar_t & Tile::getChar() const {
    return ch;
}

void Tile::print(int x, int y) const {
    mvprintw(x, y, "%lc", ch);
}
