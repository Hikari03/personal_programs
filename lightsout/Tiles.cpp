#include "Tiles.h"

Tiles::Tiles(unsigned int width_, unsigned int height_) : width(width_), height(height_) {

    resize(width_, height_);
}

void Tiles::resize(unsigned int width_, unsigned int height_) {

    tiles.resize(height_);
        for(unsigned int i = 0; i < height_; i++) {
            tiles[i].resize(width_);
        }

    for(unsigned int i = 0; i < height_; i++) {
        for(unsigned int j = 0; j < width_; j++) {
            std::shared_ptr<Tile> tile = std::make_shared<Tile>();
            tile->setChar(L' ');
            tiles[i][j] = tile;
        }
    }
}

void Tiles::insertTile(unsigned int x, unsigned int y, wchar_t c) {

    if(x < width && y < height) {
        tiles[y][x] = std::make_shared<Tile>();
        tiles[y][x]->setChar(c);
    }

    throw std::out_of_range("setTile: Tile index out of range: " + std::to_string(x) + ", " + std::to_string(y));
}

std::shared_ptr<Tile> Tiles::getTile(unsigned int x, unsigned int y) {

    if(x < width && y < height) {
        return tiles[y][x];
    }

    throw std::out_of_range("getTile: Tile index out of range: " + std::to_string(x) + ", " + std::to_string(y));
}

std::shared_ptr<Tile> & Tiles::setColor(unsigned int x, unsigned int y, int color) {

    if(x >= width || y >= height)
        throw std::out_of_range("insertColorTile: Tile index out of range: " + std::to_string(x) + ", " + std::to_string(y));

    if(color > 255 || color < 0)
        throw std::out_of_range("insertColorTile: Color index out of range: " + std::to_string(color));


    if(tiles[y][x]->getType() == Tile::Type::ColorTile) {
        tiles[y][x]->setColor(color);
    } else {
        std::shared_ptr<ColorTile> tile = std::make_shared<ColorTile>();
        tile->setChar(tiles[y][x]->getChar());
        tile->setColor(color);
        tiles[y][x] = tile;
    }

    return tiles[y][x];

}

void Tiles::clear() {

    for(unsigned int i = 0; i < height; i++) {
        for(unsigned int j = 0; j < width; j++) {
            tiles[i][j] = std::make_shared<Tile>();
        }
    }

}
