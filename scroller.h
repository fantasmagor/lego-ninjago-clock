#include "element.h"
#include "tools.h"

#ifndef Included_Scroller

#define Included_Scroller
class Scroller: public Element {
  private:
    uint8_t _x;
    uint8_t _y;
    uint8_t _areaPixLength;
    uint8_t _textPixLength;
    int16_t _i = 0;
    char* _text = "";
    const uint8_t* _font;

  public:
    Scroller(char*, uint8_t, uint8_t, uint8_t, const uint8_t*);
    virtual void next();
    void drawFrame();
    void setText(String);
    char* getText();
};

Scroller::Scroller(char* name, uint8_t x, uint8_t y, uint8_t length, const uint8_t* font) {
  setName(name);
  _x = x;
  _y = y;
  _areaPixLength = length + 4;
  _font = font;
};

void Scroller::drawFrame() {
  u8g2.setClipWindow(_x - 1, _y - 1, _x + _areaPixLength - 1, _y + 14);
  u8g2.setDrawColor(1);
  u8g2.drawFrame(_x - 1, _y - 1, _areaPixLength, 14);
  u8g2.setDrawColor(0);
  u8g2.drawFrame(_x, _y, _areaPixLength - 2, 12);
}

void Scroller::next() {
   if (sizeof(_text)==0) {
     return;
   }

  u8g2.setDrawColor(1);
  _i--;
  u8g2.setFont(_font);
  u8g2.drawUTF8(_x + _i, _y + 9, _text);
  drawFrame();

  if (_i < -(int)(_textPixLength + _areaPixLength)) {
    _i = _areaPixLength;
  }
}

void Scroller::setText(String text) {
  _text = string2char(text);
  u8g2.setFont(_font);
  _textPixLength = -(u8g2.getUTF8Width(_text));
  _i = _areaPixLength;
}

char* Scroller::getText() {
  return _text;
}

#endif
