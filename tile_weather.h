#include "tile.h"

#ifndef Included_TileWeather

#define Included_TileWeather

class TileWeather: public Tile {
  private:
    uint8_t _x;
    uint8_t _y;
    String _day_temperature = "";
    String _night_temperature = "";
    char _icon[1];
    void drawBackground();
    void drawContent();

  public:
    TileWeather(char*, uint8_t, uint8_t);
    void update(const JsonDocument&);
};

TileWeather::TileWeather(char* name, uint8_t x, uint8_t y) {
  setName(name);
  _x = x;
  _y = y;
  _icon[0] = (char)64;
};

void TileWeather::update(const JsonDocument& data) {
  if (data.containsKey("dayTemp")) {
    int dayTemp = data["dayTemp"];
    Serial.print("[Weather] New day temperature: ");
    Serial.println(dayTemp);
    _day_temperature = String(dayTemp) + "°C";
  }

  if (data.containsKey("nightTemp")) {
    int nightTemp = data["nightTemp"];
    Serial.print("[Weather] New night temperature: ");
    Serial.println(nightTemp);
    _night_temperature = String(nightTemp) + "°C";
  }

  if (data.containsKey("icon")) {
    _icon[0] = (char)data["icon"];
    Serial.print("[Weather] New icon: ");
    Serial.println(_icon);
  }
}

// private
void TileWeather::drawBackground() {
  u8g2.setDrawColor(1);
  u8g2.drawBox(_x, _y, 48, 29);
  u8g2.setDrawColor(0);
  u8g2.drawBox(_x + 1, _y + 14, 27, 14);
}

void TileWeather::drawContent() {
  u8g2.setDrawColor(1);
  u8g2.setFont(u8g2_font_5x8_tf);
  u8g2.drawUTF8(_x + 3, _y + 24, _night_temperature.c_str());
  
  u8g2.setDrawColor(0);
  u8g2.setFont(u8g2_font_5x8_tf);
  u8g2.drawUTF8(_x + 3, _y + 11, _day_temperature.c_str());
  u8g2.setFont(u8g2_font_open_iconic_weather_2x_t);
  u8g2.drawStr(_x + 31, _y + 22, _icon);
}
#endif
