#include <iostream>
#include "Renderer.h"
#include "Tiles.h"


int main(int argc, char **argv) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <width> <height>" << std::endl;
        return 1;
    }

    int width = std::stoi(argv[1]);
    int height = std::stoi(argv[2]);

    Tiles tiles(width,height);
    Renderer renderer(tiles);

    // Set up mouse event throwing
    mousemask(BUTTON1_PRESSED, nullptr);
    MEVENT event;

    auto good = renderer.initColor(10,0);
    auto bad = renderer.initColor(9,0);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            tiles.setColor(i, j, bad)->setChar(L'☐');
        }
    }

    while(true) {
        getch();

        if (getmouse(&event) == OK) {
            if (event.x >= width || event.y >= height)
                continue;
            if (event.bstate & BUTTON1_PRESSED) { // set tile and surrounding tiles to opposite color
                if (tiles.getTile(event.x, event.y)->getColor() == good) {
                    tiles.setColor(event.x, event.y, bad);
                } else {
                    tiles.setColor(event.x, event.y, good);
                }

                if (event.x > 0) {
                    if (tiles.getTile(event.x - 1, event.y)->getColor() == good) {
                        tiles.setColor(event.x - 1, event.y, bad);
                    } else {
                        tiles.setColor(event.x - 1, event.y, good);
                    }
                }

                if (event.x < width - 1) {
                    if (tiles.getTile(event.x + 1, event.y)->getColor() == good) {
                        tiles.setColor(event.x + 1, event.y, bad);
                    } else {
                        tiles.setColor(event.x + 1, event.y, good);
                    }
                }

                if (event.y > 0) {
                    if (tiles.getTile(event.x, event.y - 1)->getColor() == good) {
                        tiles.setColor(event.x, event.y - 1, bad);
                    } else {
                        tiles.setColor(event.x, event.y - 1, good);
                    }
                }

                if (event.y < height - 1) {
                    if (tiles.getTile(event.x, event.y + 1)->getColor() == good) {
                        tiles.setColor(event.x, event.y + 1, bad);
                    } else {
                        tiles.setColor(event.x, event.y + 1, good);
                    }
                }

            }
        }
        renderer.print();
    }
}