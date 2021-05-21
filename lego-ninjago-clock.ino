#include <Arduino.h>
#include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//#include <ESP8266WebServer.h>
#include <CronAlarms.h>
#include <PubSubClient.h>
#include <Scheduler.h>

U8G2_SSD1309_128X64_NONAME0_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 13, /* cs=*/ 15, /* dc=*/ 4, /* reset=*/ 0);

#include "tools.h";
#include "message_client.h"
#include "secrets.h"
#include "loader.h"
#include "dispatcher.h"

#include "screen.h"
#include "tile_alarm.h"
#include "tile_clock.h"
#include "tile_icon.h"
#include "tile_roblox.h"
#include "tile_scroller.h"
#include "tile_text.h"
#include "tile_weather.h"
#include "tile_weekday.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

// Set your Static IP address
IPAddress local_IP(192, 168, 0, 200);
// Set your Gateway IP address
IPAddress gateway(192, 168, 0, 1);

IPAddress subnet(255, 0, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

BearSSL::WiFiClientSecure client;
PubSubClient mqtt(client);

BearSSL::X509List cert(AWS_CERT_CA);
BearSSL::X509List client_crt(AWS_CERT_CRT);
BearSSL::PrivateKey key(AWS_KEY_PRIVATE);

Screen screen;
//Icon icon1("icon", 50, 15);
TileScroller scroller1("scroller", 0, 0, 124);
TileClock clock1("clock", 0, 17);
TileWeather weather1("weather", 80, 17);
TileWeekday weekday1("weekday", 0, 48);
TileAlarm alarm1("alarm", 25, 48);
TileRoblox roblox1("roblox", 80, 48);


Dispatcher* dispatcher;
MessageClient* messageClient;

class ScreenTask : public Task {
protected:
    void loop()  {
        screen.tick();
    }
} screenTask;

class CronTask : public Task {
protected:
    void loop()  {
        Cron.delay();
        messageClient->loop();
    }
} cronTask;

void checkMQTTConnection() {
    messageClient->checkConnection();
}

void setup(void) {
    Serial.begin(115200);
    u8g2.begin();
    u8g2.enableUTF8Print();

    dispatcher = new Dispatcher(&screen);
    messageClient = new MessageClient(&mqtt, dispatcher);
    
    Loader loader;
    loader.tick();
    
    if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
        Serial.println("WiFi Failed to configure");
    }
  
    WiFi.begin(STASSID, STAPSK);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    loader.tick();
  
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(STASSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    loader.tick();
      
    setClock();
    client.setTrustAnchors(&cert);
    client.setClientRSACert(&client_crt, &key);
    client.setX509Time(time(nullptr));
    
    Serial.println("Done...");
    loader.tick();
  
    scroller1.setText(F("Cześć, jestem ludzik LEGO Ninjago."));
  //  scroller1.setText(F("Cześć, jestem ludzik LEGO Ninjago. Nazywam się Jay. Co u Ciebie słychać?"));
  //  scroller1.setText(F("Hello! I'm a lego Ninjago figure. How are you?"));
    screen.add(&clock1);
    screen.add(&scroller1);
    screen.add(&weather1);
    screen.add(&weekday1);
    screen.add(&alarm1);
    screen.add(&roblox1);
  
    loader.done();
    messageClient->init();

    Cron.create("0 * * * * *", checkMQTTConnection, false);
    Scheduler.start(&screenTask);
    Scheduler.start(&cronTask);
    Scheduler.begin();
}

void loop(void) {}
