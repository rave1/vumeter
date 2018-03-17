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
int prevPeak = 0;
int peak = 0;
int sound, i, j;
float brightness = 0.1;

uint32_t red = ring.Color(255 * brightness, 0, 0);
uint32_t green = ring.Color(0, 255 * brightness ,0);
uint32_t blue = ring.Color(0, 0, 255 * brightness);
uint32_t magenta = ring.Color(230 * brightness,0 * brightness,255 * brightness);
uint32_t turk = ring.Color(85 * brightness,31 * brightness,67 * brightness);
uint32_t darkerturk = ring.Color(95 * brightness,30 * brightness,225 * brightness);
uint32_t pink = ring.Color(255 * brightness,7 * brightness,120 * brightness);
uint32_t ringColor[16] = {magenta, magenta, magenta, green, green, green, green, green, green, green, green, green, pink, pink, pink, red};
void storePrev(){
    prevSound = sound;
    prevMapped = mappedValue;
    prevPeak = peak;
}
void readvalues() {
    for (i = 0; i<= numofReadings; i++)
      sound += analogRead(JACK);
    sound /= numofReadings;
    sound *= sensitivity;
    mappedValue = map(sound, minAnalog, maxAnalog, 0, ledCount - 1);
    peak = mappedValue + 1;
}
void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(DATA_OUT, OUTPUT);
    ring.begin();
    ring.show();
}

void drawValues();

void shutoff() {
  mappedValue = 0;
  ring.show();
}
void loop() {
      readvalues();
      Serial.println(sound);
      drawValues();
      ring.show();
      storePrev();
}

void drawValues() {
  for (i = 0; i < mappedValue; i++) {
    ring.setPixelColor(i, ringColor[i]);
  //  ring.setPixelColor(peak, blue);
  }
  for (i = prevMapped; i >= mappedValue; i--){
    ring.setPixelColor(i, 0);
//    ring.setPixelColor(prevPeak, 0);
    //ring.setPixelColor(i++, 0);
  }
}
