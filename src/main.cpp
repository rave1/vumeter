#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define DATA_OUT 6
#define JACK A0
#define numofReadings 10

int ledCount = 16;
Adafruit_NeoPixel ring = Adafruit_NeoPixel(ledCount, DATA_OUT, NEO_GRB + NEO_KHZ800);
int minAnalog = 0;
int maxAnalog = 300;
int maxSens = 4 * 255;
int mappedValue = 0;
float sensitivity = 1;
int middleLed = 0;
int prevSound = 0;
int prevMapped = 0;
int sound, i;

uint32_t red = ring.Color(255, 0, 0);
uint32_t green = ring.Color(0, 255 ,0);
uint32_t ringColor[16] = {red, red, red, green, green, green, green, green, green, green, green, green, green, red, red, red};

void storePrev(){
    prevSound = sound;
    prevMapped = mappedValue;
}
void readvalues() {
    for (i = 0; i<= numofReadings; i++)
      sound += analogRead(JACK);
    sound /= numofReadings;
    sound *= sensitivity;
    mappedValue = map(sound, minAnalog, maxAnalog, 0, ledCount - 1);
}
void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(DATA_OUT, OUTPUT);
    ring.begin();
    ring.show();
}
void drawValues() {
  for (i = 0; i < mappedValue; i++)
    ring.setPixelColor(i, ringColor[i]);
    for (i = prevMapped; i >= mappedValue; i--)
      ring.setPixelColor(i, 0);
}
void shutoff() {
  mappedValue = 0;
  ring.show();
}
void loop() {
    // put your main code here, to run repeatedly:
      readvalues();
      Serial.println(mappedValue);
      drawValues();
      ring.show();
      storePrev();
    //shutoff();
}
