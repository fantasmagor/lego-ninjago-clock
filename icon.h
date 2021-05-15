#include "element.h"

#ifndef Included_Icon

#define Included_Icon
class Icon: public Element {
  private:
    uint8_t _x;
    uint8_t _y;

  public:
    Icon(char*, uint8_t, uint8_t);
    virtual void next();
};

Icon::Icon(char* name, uint8_t x, uint8_t y) {
  setName(name);
  _x = x;
  _y = y;
};

void Icon::next() {
//    Serial.println("Icon");
}


#endif
