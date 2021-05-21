#include "tile.h"
#include "tools.h"

#ifndef Included_TileScroller

#define Included_TileScroller
class TileScroller: public Tile {
    private:
        uint8_t _x;
        uint8_t _y;
        uint8_t _areaPixLength;
        int16_t _textPixLength;
        int16_t _i = 0;
        int16_t _j = 0;
        char* _text = "";
        const uint8_t* _font = u8g2_font_t0_11_te;
        void drawContent();
        void drawFrame();
  
    public:
        TileScroller(char*, uint8_t, uint8_t, uint8_t);
        void update(const JsonDocument&);
        void setText(String);
};

TileScroller::TileScroller(char* name, uint8_t x, uint8_t y, uint8_t length) {
    setName(name);
    _x = x;
    _y = y;
    _areaPixLength = length + 4;
};

void TileScroller::update(const JsonDocument& data) {
    if (data.containsKey("text")) {
        String text = data["text"];
        Serial.print("[Scroller] New text: ");
        Serial.println(text);
        setText(text);
    }
}

void TileScroller::setText(String text) {
    _text = string2char(text);
    u8g2.setFont(_font);
    _text = string2char((String)" *** " + _text);
    _textPixLength = u8g2.getUTF8Width(_text);
    _i = _areaPixLength;
  
  
    if (_textPixLength > _areaPixLength) {
        _j = _areaPixLength + _textPixLength;
    } else {
        _text = string2char((String)_text + " *** ");
        _textPixLength = u8g2.getUTF8Width(_text);
    }
}

// private
void TileScroller::drawFrame() {
//  u8g2.setClipWindow(_x - 1, _y /- 1, _x + _areaPixLength - 1, _y + 14);
    u8g2.setDrawColor(1);
    u8g2.drawFrame(_x, _y, _areaPixLength, 15);
    u8g2.setDrawColor(0);
    u8g2.drawFrame(_x + 1, _y + 1, _areaPixLength - 2, 13);
}

void TileScroller::drawContent() {
   if (sizeof(_text)==0) {
      return;
   }
  
    u8g2.setDrawColor(1);
    u8g2.setFont(_font);
  
    if(--_i < _areaPixLength) {
        u8g2.drawUTF8(_x + _i + 2, _y + 11, _text);  
    
        if (_i < -(int16_t)(_textPixLength)) {
            _i = _textPixLength > _areaPixLength ? _textPixLength : _areaPixLength;
        }
    }

    if (_textPixLength > _areaPixLength && --_j < _areaPixLength) {
        u8g2.drawUTF8(_x + _j + 2, _y + 11, _text);
      
        if (_j < -(int16_t)(_textPixLength)) {
            _j = _textPixLength;
        }
    }

//  Serial.print("_areaPixLength: ");
//  Serial.print(_areaPixLength);
//  Serial.print(", _textPixLength: ");
//  Serial.print(_textPixLength);
//  Serial.print(", i: ");
//  Serial.print(_i);
//  Serial.print(", j: ");
//  Serial.println(_j);
}
#endif
