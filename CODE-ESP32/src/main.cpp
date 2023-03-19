#include <Arduino.h>

// Load Wi-Fi library
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Arduino_JSON.h>
#include "SPIFFS.h"

int relust = 100;
// chân ST_CP của 74HC595
int latchPin1 = 23;
// chân SH_CP của 74HC595
int clockPin1 = 22;
// Chân DS của 74HC595
int dataPin1 = 21;

// chân ST_CP của 74HC595
int latchPin2 = 19;
// chân SH_CP của 74HC595
int clockPin2 = 18;
// Chân DS của 74HC595
int dataPin2 = 5;

const int Seg[10] = {
    0b11000000, // 0 - các thanh từ a-f sáng
    0b11111001, // 1 - chỉ có 2 thanh b,c sáng
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10010000, // 9
};

// Replace with your network credentials
const char *ssid = "NNE";
const char *password = "123456789";

AsyncWebServer server(80);

AsyncEventSource events("/events");

JSONVar readings;

void initSPIFFS()
{
  if (!SPIFFS.begin())
  {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  Serial.println("SPIFFS mounted successfully");
}

// Initialize WiFi
void initWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.println(WiFi.localIP());
}

void display1(int x)
{
  digitalWrite(latchPin1, LOW);
  shiftOut(dataPin1, clockPin1, MSBFIRST, Seg[x]);
  digitalWrite(latchPin1, HIGH);
}

void display2(int x)
{
  digitalWrite(latchPin2, LOW);
  shiftOut(dataPin2, clockPin2, MSBFIRST, Seg[x]);
  digitalWrite(latchPin2, HIGH);
}
void allOFF()
{
  display1(0);
  display1(0);
  display2(0);
  display2(0);

  digitalWrite(25, 0);
  digitalWrite(26, 0);
  digitalWrite(27, 0);

  digitalWrite(14, 0);
  digitalWrite(12, 0);
  digitalWrite(13, 0);
}

void red()
{
  display1(0);
  display1(0);
  display2(0);
  display2(0);

  digitalWrite(25, 1);
  digitalWrite(26, 0);
  digitalWrite(27, 0);

  digitalWrite(14, 1);
  digitalWrite(12, 0);
  digitalWrite(13, 0);
}

void yellowBlink()
{
  display1(0);
  display1(0);
  display2(0);
  display2(0);

  digitalWrite(25, 0);
  digitalWrite(26, 1);
  digitalWrite(27, 0);

  digitalWrite(14, 0);
  digitalWrite(12, 1);
  digitalWrite(13, 0);

  delay(200);

  digitalWrite(25, 0);
  digitalWrite(26, 0);
  digitalWrite(27, 0);

  digitalWrite(14, 0);
  digitalWrite(12, 0);
  digitalWrite(13, 0);
}

void allON()
{
  for (int i = 14; i > 3; i--)
  {
    digitalWrite(25, 1);
    digitalWrite(26, 0);
    digitalWrite(27, 0);

    digitalWrite(14, 0);
    digitalWrite(12, 0);
    digitalWrite(13, 1);

    display1(int(i % 10));
    display1(int(i / 10));
    display2(int((i - 4) % 10));
    display2(int((i - 4) / 10));
    delay(1000);
  }
  for (int i = 3; i >= 0; i--)
  {
    digitalWrite(25, 1);
    digitalWrite(26, 0);
    digitalWrite(27, 0);

    digitalWrite(14, 0);
    digitalWrite(12, 1);
    digitalWrite(13, 0);

    display1(int(i % 10));
    display1(int(i / 10));
    display2(int(i % 10));
    display2(int(i / 10));
    delay(1000);
  }

  for (int i = 14; i > 3; i--)
  {
    digitalWrite(25, 0);
    digitalWrite(26, 0);
    digitalWrite(27, 1);

    digitalWrite(14, 1);
    digitalWrite(12, 0);
    digitalWrite(13, 0);

    display2(int(i % 10));
    display2(int(i / 10));
    display1(int((i - 4) % 10));
    display1(int((i - 4) / 10));
    delay(1000);
  }
  for (int i = 3; i >= 0; i--)
  {
    digitalWrite(25, 0);
    digitalWrite(26, 1);
    digitalWrite(27, 0);

    digitalWrite(14, 1);
    digitalWrite(12, 0);
    digitalWrite(13, 0);

    display2(int(i % 10));
    display2(int(i / 10));
    display1(int(i % 10));
    display1(int(i / 10));
    delay(1000);
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(latchPin1, OUTPUT); // pin load lane 1 3 (23)
  pinMode(clockPin1, OUTPUT); // pin sclk land 1 3 (22)
  pinMode(dataPin1, OUTPUT);  // pin sdi land 1 3 (21)

  pinMode(latchPin2, OUTPUT); // pin load lane 2 4 (19)
  pinMode(clockPin2, OUTPUT); // pin sclk land 2 4 (18)
  pinMode(dataPin2, OUTPUT);  // pin sdi land 2 4 (5)

  pinMode(25, OUTPUT); // led red lane 1 3
  pinMode(26, OUTPUT); // led yellow lane 1 3
  pinMode(27, OUTPUT); // led green lane 1 3

  pinMode(14, OUTPUT); // led red lane 2 4
  pinMode(12, OUTPUT); // led yellow lane 2 4
  pinMode(13, OUTPUT); // led green lane 2 4

  digitalWrite(25, 0);
  digitalWrite(26, 0);
  digitalWrite(27, 0);

  digitalWrite(14, 0);
  digitalWrite(12, 0);
  digitalWrite(13, 0);

  initWiFi();
  initSPIFFS();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/index.html", "text/html"); });

  server.serveStatic("/", SPIFFS, "/");

  server.on("/onALL", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              allOFF();
              Serial.println("onALL");
              relust = 0;
              request->send(200, "text/plain", "OK"); });

  server.on("/stop", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              allOFF();
              Serial.println("stop");
              relust = 1;
              request->send(200, "text/plain", "OK"); });

  server.on("/red", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              allOFF();
              Serial.println("red");
              relust = 2;
              request->send(200, "text/plain", "OK"); });

  server.on("/yellowBlink", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              allOFF();
              Serial.println("yellowBlink");
              relust = 3;
              request->send(200, "text/plain", "OK"); });

  server.addHandler(&events);

  server.begin();
}

void loop()
{
  if (relust == 0)
  {
    allON();
  }
  if (relust == 1)
  {
    allOFF();
  }
  if (relust == 2)
  {
    red();
  }
  if (relust == 3)
  {
    yellowBlink();
  }
}