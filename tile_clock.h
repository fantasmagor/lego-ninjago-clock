#include <ezTime.h>
#include "tools.h"
#include "tile.h"

#ifndef Included_TileClock

#define Included_TileClock

class TileClock: public Tile {
    private:
        uint8_t _x;
        uint8_t _y;
        void drawBackground();
        void drawContent();
  
    public:
        TileClock(char*, uint8_t, uint8_t);
};

TileClock::TileClock(char* name, uint8_t x, uint8_t y) {
    setName(name);
    _x = x;
    _y = y;
};

// private
void TileClock::drawBackground() {
    u8g2.setDrawColor(1);
    u8g2.drawBox(_x, _y, 78, 29);
  
    u8g2.setDrawColor(0);
    u8g2.drawHLine(_x + 3, _y + 16, 72);
}

void TileClock::drawContent() {
    u8g2.setDrawColor(0);
    u8g2.setFont(u8g2_font_9x15B_tf);
    u8g2.drawStr(_x + 3, _y + 13, _tz.dateTime("H:i:s").c_str());
    u8g2.setFont(u8g2_font_6x12_te);
    u8g2.drawUTF8(_x + 6, _y + 26, _tz.dateTime("d M Y").c_str());
}
#endif
