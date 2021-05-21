#include <ezTime.h>
#include "tile.h"

#ifndef Included_TileAlarm

#define Included_TileAlarm
class TileAlarm: public Tile {
    private:
        uint8_t _x;
        uint8_t _y;
        long _value = 0;
        boolean _active = false;
        char _icon[1];
        void drawBackground();
        void drawContent();
  
    public:
        TileAlarm(char*, uint8_t, uint8_t);
        void update(const JsonDocument&);
        virtual void tick();
};

TileAlarm::TileAlarm(char* name, uint8_t x, uint8_t y) {
    setName(name);
    _icon[0] = (char)65;
    _x = x;
    _y = y;
};

void TileAlarm::tick() {
    drawBackground();
    drawContent();
};

void TileAlarm::update(const JsonDocument& data) {
    if (data.containsKey("value")) {
        _value = ((long)data["value"] % 1440) * 60;
        Serial.print("[Alarm] New value: ");
        Serial.println(_value);
    }
}

// private
void TileAlarm::drawBackground() {
    u8g2.setDrawColor(1);
    u8g2.drawBox(_x, _y, 53, 16);
}

void TileAlarm::drawContent() {
    u8g2.setDrawColor(0);
    u8g2.setFont(u8g2_font_open_iconic_embedded_1x_t);
    u8g2.drawStr(_x + 4, _y + 12, _icon);
    u8g2.setFont(u8g2_font_mozart_nbp_tn);
    u8g2.drawUTF8(_x + 18, _y + 12, _tz.dateTime(_value, "H:i").c_str());
}
#endif
