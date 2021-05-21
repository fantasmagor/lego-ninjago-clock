#include "tile.h"

#ifndef Included_Screen

#define Included_Screen
#define MAX_ELEMENTS 10

class Screen {
    private:
        Tile* _tiles[MAX_ELEMENTS];
        uint8_t _tileCounter = 0;
        Timezone _tz;
        int8_t findByName(char*);
  
    public:
        Screen();
        void tick();
        void add(Tile*);
        void process(char*);
        void update(char*, const JsonDocument&);
};

Screen::Screen() {
    Serial.println("Setting timezone");
    _tz.setCache(0);
    _tz.setLocation("Europe/London");
}

void Screen::tick() {
    u8g2.clearBuffer();
  
    for (uint8_t i = 0; i < _tileCounter; i++) {
        _tiles[i]->tick();
    }
  
    u8g2.sendBuffer();
}

void Screen::add(Tile *tile) {
    tile->init();
    tile->setTimezone(_tz);
    _tiles[_tileCounter++] = tile;
}

void Screen::update(char* tileName, const JsonDocument& data) {
    int8_t i = findByName(tileName);
    if (i > -1) {
  //    Serial.print("[Screen] Data: ");
  //    Serial.println(data); 
        _tiles[i]->update(data);
    }
}


int8_t Screen::findByName(char* name) {
    for (int8_t i = 0; i < _tileCounter; i++) {
        if (String(name).equals(_tiles[i]->getName())) {
            return i;
        }
    }
  
    return -1;
}
#endif
