#include "tile.h"

#ifndef Included_TileIcon

#define Included_TileIcon
class TileIcon: public Tile {
    private:
        uint8_t _x;
        uint8_t _y;
        void drawBackground();
        void drawContent();

    public:
        TileIcon(char*, uint8_t, uint8_t);
};

TileIcon::TileIcon(char* name, uint8_t x, uint8_t y) {
    setName(name);
    _x = x;
    _y = y;
};

// private
void TileIcon::drawBackground() {}

void TileIcon::drawContent() {}
#endif
