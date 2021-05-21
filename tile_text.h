#include "tile.h"

#ifndef Included_TileText

#define Included_TileText
class TileText: public Tile {
  private:
    uint8_t _x;
    uint8_t _y;
    void drawBackground();
    void drawContent();

  public:
    TileText(char*, uint8_t, uint8_t, uint8_t length, const uint8_t* font);
};

TileText::TileText(char* name, uint8_t x, uint8_t y, uint8_t length, const uint8_t* font) {
  setName(name);
  _x = x;
  _y = y;
};

// private
void TileText::drawBackground() {}

void TileText::drawContent() {}
#endif
