#ifndef Included_Tile

#define Included_Tile
class Tile {
    protected:
        Timezone _tz;
    
    private:
        char* _name;
        virtual void drawBackground();
        virtual void drawContent();
        virtual void drawFrame();
      
    public:
        Tile ();
        virtual void init();
        virtual void tick();
        virtual void update(const JsonDocument&);
        char* getName();
        void setName(char*);
        void setTimezone(Timezone);
};

Tile::Tile () {}
void Tile::tick() {
    drawBackground();
    drawContent();
    drawFrame();
};

void Tile::init() {};

void Tile::setTimezone(Timezone tz) {
    _tz = tz;
};

void Tile::update(const JsonDocument& data) {};

char* Tile::getName() {
    return _name;
};

void Tile::setName(char* name) {
    _name = name;
};

// private
void Tile::drawBackground() {}

void Tile::drawContent() {}

void Tile::drawFrame() {}
#endif
