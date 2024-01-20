#include "Renderer.h"

Renderer::Renderer(std::vector<std::vector<std::shared_ptr<Tile>>> & tiles_, unsigned width_, unsigned height_) : tiles(tiles_) {
    setlocale(LC_CTYPE,"");

    width = width_;
    height = height_;

    tiles.resize(height);
    for(int i = 0; i < height; i++) {
        tiles[i].resize(width);
    }

    prevTiles.resize(height);
    for(int i = 0; i < height; i++) {
        prevTiles[i].resize(width);
    }

    for(unsigned int i = 0; i < height; i++) {
        for(unsigned int j = 0; j < width; j++) {
            std::shared_ptr<Tile> tile = std::make_shared<Tile>();
            tile->setChar(L' ');
            tiles[i][j] = tile;
        }
    }

    for(unsigned int i = 0; i < height; i++) {
        for(unsigned int j = 0; j < width; j++) {
            std::shared_ptr<Tile> tile = std::make_shared<Tile>();
            tile->setChar(L' ');
            prevTiles[i][j] = tile;
        }
    }

    copyTiles();

    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, true);
    //resize_term(height, width);
    refresh();
}


void Renderer::print() {

    std::shared_ptr<Tile> tile;
    bool changed = false;

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            tile = tiles[i][j];

            if(tile->getChar() != prevTiles[i][j]->getChar()) {
                tile->print(i, j);
                changed = true;
            }
        }
    }

    if(changed) {
        refresh();
        copyTiles();
    }
}

void Renderer::copyTiles() {
    //prevTiles = tiles; is shallow copy

    prevTiles.resize(height);
    for(int i = 0; i < height; i++) {
        prevTiles[i].resize(width);
    }

    for(unsigned int i = 0; i < height; i++) {
        for(unsigned int j = 0; j < width; j++) {
            auto prevTile = prevTiles[i][j]->getChar();
            auto tile = tiles[i][j]->getChar();
            if(prevTile != tile) {
                std::shared_ptr<Tile> newTile = std::make_shared<Tile>();
                newTile->setChar(tile);
                prevTiles[i][j] = newTile;
            }
        }
    }

}
