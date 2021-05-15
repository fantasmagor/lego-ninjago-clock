#include "element.h"

#ifndef Included_TextScreenElement

#define Included_TextScreenElement
class Text: public Element {
  private:
    uint8_t _x;
    uint8_t _y;

  public:
    Text(char*, uint8_t, uint8_t, uint8_t length, const uint8_t* font);
    virtual void next();
};

Text::Text(char* name, uint8_t x, uint8_t y, uint8_t length, const uint8_t* font) {
  setName(name);
  _x = x;
  _y = y;
};

void Text::next() {
//  Serial.println(getName());
}


#endif
