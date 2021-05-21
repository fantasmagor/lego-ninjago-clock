#include <ezTime.h>
#include "tile.h"

#ifndef Included_TileWeekday

#define Included_TileWeekday

class TileWeekday: public Tile {
  private:
    uint8_t _x;
    uint8_t _y;
    void drawBackground();
    void drawContent();

  public:
    TileWeekday(char*, uint8_t, uint8_t);
};

TileWeekday::TileWeekday(char* name, uint8_t x, uint8_t y) {
  setName(name);
  _x = x;
  _y = y;
};

// private
void TileWeekday::drawBackground() {
  u8g2.setDrawColor(1);
  u8g2.drawBox(_x, _y, 23, 22);
}

void TileWeekday::drawContent() {
  u8g2.setDrawColor(0);
  u8g2.setFont(u8g2_font_6x13_te);
  u8g2.drawUTF8(_x + 3, _y + 12, _tz.dateTime("D").c_str());
}
#endif
