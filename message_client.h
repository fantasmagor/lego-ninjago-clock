#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "secrets.h"
#include "dispatcher.h"

#ifndef Included_MessageClient

#define AWS_IOT_UPDATE_TOPIC "LegoNinjagoClock/update"
#define AWS_IOT_INIT_TOPIC "LegoNinjagoClock/init"
#define DEVICE_NAME "LegoNinjagoClock"

#define Included_MessageClient
class MessageClient {
    private:
        PubSubClient* _mqtt;
        Dispatcher* _dispatcher;
        boolean _initialised = false;
        void receiveMessage(char*, byte*, unsigned int);
      
    public:
        MessageClient(PubSubClient*, Dispatcher*);
        void checkConnection();
        void init();
        void loop();
};

MessageClient::MessageClient(PubSubClient *mqtt, Dispatcher *dispatcher) {
    _mqtt = mqtt;
    _dispatcher = dispatcher;
    _mqtt->setServer(AWS_IOT_ENDPOINT, 8883);
    _mqtt->setCallback([&](char* topic, byte* payload, unsigned int length) {
        Serial.println(length);
        receiveMessage(topic, payload, length); 
    });
    _mqtt->setKeepAlive(120);
    _mqtt->setBufferSize(1024);
}

void MessageClient::init() {
    MessageClient::checkConnection();
    _initialised = true;
}

void MessageClient::receiveMessage(char* topic, byte* payload, unsigned int length) {
    Serial.print("Receiving an update msg: ");
    Serial.println((char*)payload);
    Serial.println(topic);
  
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
  
    _dispatcher->dispatchMessage(doc);
}

void MessageClient::checkConnection() {
    if (_mqtt->state() != MQTT_CONNECTED) {
        Serial.print("State: ");
        Serial.print(_mqtt->state());
        Serial.println(" (DISCONNECTED)");
        Serial.println("Attempting MQTT connection...");
        
        if (_mqtt->connect(DEVICE_NAME)) {
            Serial.println("CONNECTED");
            _mqtt->subscribe(AWS_IOT_UPDATE_TOPIC);

             if (!_initialised) {
                 Serial.println("Sending initialisation message...");
                 _mqtt->publish(AWS_IOT_INIT_TOPIC, "{}");
             }
        } else {
            Serial.println("Failed, try later");
        }
    } else {
        Serial.println("Already CONNECTED, nothing to do");
    }
  
    Serial.print("Connection state: ");
    Serial.println(_mqtt->state());
}

void MessageClient::loop() {
    _mqtt->loop();
}
#endif
