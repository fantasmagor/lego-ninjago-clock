#include "scroller.h"

#ifndef Included_Screen

#define Included_Screen
#define MAX_ELEMENTS 10

class Screen {
  private:
    Element *_elements[MAX_ELEMENTS];
    int findByName(char*);

  public:
    void next();
    void add(Element*, int);
    void process(char*);
};

void Screen::next() {
//  Serial.println("Screen");
  u8g2.clearBuffer();

  for (uint8_t i = 0; i < MAX_ELEMENTS; i++) {
    if (_elements[i]) {
      _elements[i]->next();
    }
  }

  u8g2.sendBuffer();
}

void Screen::add(Element *element, int i) {
  _elements[i] = element;
}

void Screen::process(char* data) {  
  Serial.println(data[0]);
  findByName(data);
}

int Screen::findByName(char* name) {
  for (uint8_t i = 0; i < MAX_ELEMENTS; i++) {
    if (_elements[i] && _elements[i]->getName() == name) {
      return i;
    }
  }

  return NULL;
}

#endif
