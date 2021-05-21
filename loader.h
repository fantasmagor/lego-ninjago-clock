#ifndef Included_Loader

#define Included_Loader

#define MAX_LOADER_PARTS 5

String firsts[MAX_LOADER_PARTS] = {
    "Odsaczanie",
    "Gotowanie",
    "Obieranie",
    "Mieszanie",
    "Krojenie"
}; 

String lasts[MAX_LOADER_PARTS] = {
    "ziemniaczków",
    "buraczków",
    "marcheweczek",
    "kalafiorków",
    "kurczaczka"
}; 

class Loader {
    private:
        void redraw(boolean);
        String _messages[MAX_LOADER_PARTS + 1];
        int _c = 0;
      
    public:
        void tick();
        void done();
};

void Loader::tick() {
    return;
    int r1 = random(MAX_LOADER_PARTS);
    int r2 = random(MAX_LOADER_PARTS);
    boolean repeat = false;
  
    do {
        _messages[_c] = firsts[r1] + " " + lasts[r2] + "...";
    
        for (int i = 0; i < _c - 1; i++) {
            if(_messages[_c] == _messages[i]) {
                repeat = true;
                break;
            }
        }
    } while (repeat);
  
    _c++;
    redraw(false);
    delay(700);
    redraw(true);
    delay(700);
}

void Loader::done() {
    return;
    _messages[_c] = "Zupka gotowa";
    _c++;
    redraw(false);
    delay(2000);
}

void Loader::redraw(boolean withOk) {
    u8g2.clearBuffer();
    u8g2.setDrawColor(1);
    u8g2.setFont(u8g2_font_4x6_tf);
  
    for (int i = 0; i < _c; i++) {
        char* text = string2char(_messages[i] + ( withOk || i < _c - 1 ? " ok" : "" ) );
        Serial.print("Linia: ");
        Serial.print(i);
        Serial.print(" - ");      
        Serial.println(text);
        u8g2.drawUTF8(2, (70 - (_c * 10) + (i * 10)), text);
    }
  
    u8g2.sendBuffer();
}

#endif
