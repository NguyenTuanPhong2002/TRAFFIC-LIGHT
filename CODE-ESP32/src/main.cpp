#include <Arduino.h>

// Load Wi-Fi library
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Arduino_JSON.h>
#include "SPIFFS.h"

// Replace with your network credentials
const char* ssid = "CLAB";
const char* password = "123456789";

WiFiServer server(80);

AsyncEventSource events("/events");

JSONVar readings;

//chân ST_CP của 74HC595
int latchPin1 = 23;
//chân SH_CP của 74HC595
int clockPin1 = 22;
//Chân DS của 74HC595
int dataPin1 = 1;

//chân ST_CP của 74HC595
int latchPin2 = 21;
//chân SH_CP của 74HC595
int clockPin2 = 19;
//Chân DS của 74HC595
int dataPin2 = 18;

const int Seg[10] = {
  0b11000000,//0 - các thanh từ a-f sáng
  0b11111001,//1 - chỉ có 2 thanh b,c sáng
  0b10100100,//2
  0b10110000,//3
  0b10011001,//4
  0b10010010,//5
  0b10000011,//6
  0b11111000,//7
  0b10000000,//8
  0b10010000,//9
};

unsigned long lastTime = 0;
unsigned int red = 9;
unsigned int green = 6;
unsigned int yellow = 3;
unsigned long red1 = 0;
unsigned long red2 = 9;
unsigned long green1 = 0;
unsigned long green2 = 9;
unsigned long yellow1 = 0;
unsigned long yellow2 = 9;

void initSPIFFS() {
  if (!SPIFFS.begin()) {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  Serial.println("SPIFFS mounted successfully");
}

// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.println(WiFi.localIP());
}

void showtime1(int point){
  digitalWrite(latchPin1, LOW);
  shiftOut(dataPin1, clockPin1, MSBFIRST, Seg[point]);
  digitalWrite(latchPin1, HIGH);
}

void showtime2(int point){
  digitalWrite(latchPin2, LOW);
  shiftOut(dataPin2, clockPin2, MSBFIRST, Seg[point]);
  digitalWrite(latchPin2, HIGH);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  initWiFi();
  initSPIFFS();

  pinMode(latchPin1, OUTPUT);
  pinMode(clockPin1, OUTPUT);
  pinMode(dataPin1, OUTPUT);

  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);

  pinMode(36,OUTPUT); //red 1
  pinMode(39,OUTPUT); //green 1
  pinMode(34,OUTPUT); //yellow 1

  pinMode(35,OUTPUT); //red 2
  pinMode(32,OUTPUT); //green 2
  pinMode(33,OUTPUT); //yellow 2
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(36,1);
  digitalWrite(39,0);
  digitalWrite(34,0);

  digitalWrite(35,0);
  digitalWrite(32,1);
  digitalWrite(33,0);

  for(int i = 6; i > 0; i++){
    delay(1000);
    showtime1(i);
    showtime2(i);
  }

  digitalWrite(36,1);
  digitalWrite(39,0);
  digitalWrite(34,0);

  digitalWrite(35,0);
  digitalWrite(32,0);
  digitalWrite(33,1);

  for(int i = 3; i > 0; i++){
    delay(1000);
    showtime1(i);
  }

  digitalWrite(36,0);
  digitalWrite(39,1);
  digitalWrite(34,0);

  digitalWrite(35,1);
  digitalWrite(32,0);
  digitalWrite(33,0);

  for(int i = 6; i > 0; i++){
    delay(1000);
    showtime1(i);
  }

  digitalWrite(36,0);
  digitalWrite(39,0);
  digitalWrite(34,1);

  digitalWrite(35,1);
  digitalWrite(32,0);
  digitalWrite(33,0);

  for(int i = 3; i > 0; i++){
    delay(1000);
    showtime1(i);
  }

}