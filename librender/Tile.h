#pragma once
#include <string>
#include <memory>
#include <ncurses.h>

using namespace std;

/**
 * @brief Used for rendering
 * @details Tile class is a base class for all tiles, can be extended.\n
 *          It is used for rendering the game.
 */
class Tile {
public:
    Tile() = default;
    virtual ~Tile() = default;
    Tile(const Tile & other) = default;

    void setChar(wchar_t c);

    [[nodiscard]] const wchar_t & getChar() const;

    virtual void print(unsigned x, unsigned y) const;

    enum class Type {
        Tile,
        ColorTile
    };

    [[nodiscard]] Type getType() const;

protected:
    wchar_t ch = L' ';
    Type tileType = Type::Tile;
};