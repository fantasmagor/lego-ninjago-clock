#include <ArduinoJson.h>
#include "screen.h"

#ifndef Included_Dispatcher

#define Included_Dispatcher
class Dispatcher {
    private:
        Screen* _screen;
    public:
        Dispatcher(Screen*);
        void dispatchMessage(const JsonDocument&);      
};

Dispatcher::Dispatcher(Screen* screen) {
    _screen = screen;
}

void Dispatcher::dispatchMessage(const JsonDocument& json) {
    Serial.println(json.size());
    int node_length = json.size();
    
    for(int i=0; i<node_length;i++) {
        if (json[i].containsKey("element")) {
            const char* elementName = json[i]["element"];
      
            if (json[i].containsKey("data")) {
                Serial.print("[Dispatcher] New data found for element: ");
                Serial.println(elementName);
                DynamicJsonDocument data = json[i]["data"];
                _screen->update((char*)elementName, data);
            }
        }
    }
}
#endif
