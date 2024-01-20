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

    virtual void print(int x, int y) const;

protected:
    wchar_t ch = L' ';
};