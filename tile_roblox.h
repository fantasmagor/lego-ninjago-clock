#include "tile.h"

#ifndef Included_TileRoblox

#define Included_TileRoblox

class TileRoblox: public Tile {
    private:
        uint8_t _x;
        uint8_t _y;
        uint16_t _account_value = 550;
        void drawBackground();
        void drawContent();
      
    public:
        TileRoblox(char*, uint8_t, uint8_t);
        void update(const JsonDocument&);
};

TileRoblox::TileRoblox(char* name, uint8_t x, uint8_t y) {
    setName(name);
    _x = x;
    _y = y;
};

void TileRoblox::update(const JsonDocument& data) {}

// private
void TileRoblox::drawBackground() {
    u8g2.setDrawColor(1);
    u8g2.drawFrame(_x, _y, 48, 16);
}

void TileRoblox::drawContent() {
    u8g2.setDrawColor(1);
    u8g2.setFont(u8g2_font_5x7_mr);
    u8g2.drawUTF8(_x + 3, _y + 11, ("Rob: "+(String)_account_value).c_str());
}
#endif
