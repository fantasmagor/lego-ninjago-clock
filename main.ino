#include <Arduino.h>
#include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <CronAlarms.h>

U8G2_SSD1309_128X64_NONAME0_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 13, /* cs=*/ 15, /* dc=*/ 4, /* reset=*/ 0);

#include "tools.h";
#include "icon.h"
#include "screen.h"
#include "scroller.h"
#include "text.h"
#include "message_client.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

#ifndef STASSID
#define STASSID "POLSKA-CHATA"
#define STAPSK  "wodkawyborowa"
#endif

// Set your Static IP address
IPAddress local_IP(192, 168, 0, 200);
// Set your Gateway IP address
IPAddress gateway(192, 168, 0, 1);

IPAddress subnet(255, 0, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

//ESP8266WebServer server(80);

//
Screen screen;
Icon icon1("icon1", 50, 15);
Scroller scroller1("scroller1", 1, 2, 123, u8g2_font_helvB08_te);
Text text1("text1", 50, 15, 10, u8g2_font_helvB08_te);
MessageClient messageClient();
  
//const int led = 13;
void handleRoot() {  
//  if (server.hasArg("data")) {
//    char* data = strtok(string2char(server.arg("data")), "|");
//    screen.process(data);
//    server.send(200, "text/plain", "OK");
//    return;
//  }
}

void setup(void) {
  Serial.begin(115200);

  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(STASSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  u8g2.begin();  
  u8g2.enableUTF8Print();
  
  scroller1.setText("Witam, jestem ludzik LEGO Ninjago. Co u Ciebie słychać?");
  screen.add(&icon1, 0);
  screen.add(&scroller1, 1);
  screen.add(&text1, 2);

//  server.on("/", handleRoot);
//  server.begin();
//  Serial.println("HTTP server started");
  Cron.create("*/30 * * * * *", MessageClient::checkMessages, false);
}

void loop(void) {
//  server.handleClient();
  screen.next();
  Cron.delay();
//  delay(100);
}
