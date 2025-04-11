// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library
#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <SoftwareSerial.h>
SoftwareSerial softSerial(2, /*nee  =*/3);
#define LEDPIN        8
#define MAXWEIGHT 150
#define NUMPIXELS 64
#define STEPS 32
char scale_serial[200];

Adafruit_NeoPixel pixels(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500

        // a String to hold incoming data
bool stringComplete = false;

void parseWeightAlt(const char *input, float *weight) {
    char buffer[20];
    strcpy(buffer, input + 4);  // Skip "W:+ "
    char *end = strstr(buffer, "kg");  // Find "kg"
    if (end) *end = '\0';  // Replace "kg" with null terminator
    *weight = atof(buffer);  // Convert to float
}

void setup() {
    softSerial.begin(9600);
    Serial.begin(9600);


    pixels.begin();
}

void loop() {
     float weight = 0;

      if (softSerial.available()) {
          softSerial.readBytesUntil(0x0A, scale_serial, 20);
          parseWeightAlt(scale_serial, &weight);
        Serial.println(weight);
      }

    pixels.clear();
    pixels.setBrightness(250);
    for(int i=0; i<STEPS; i++) {
      if (i < map((long) weight, 0, MAXWEIGHT, 1, NUMPIXELS) ) {
          if (i < 9) {
              pixels.setPixelColor(NUMPIXELS-(2*i), pixels.Color(250, 0, 0));
          } else if( i < 18 ) {
              pixels.setPixelColor(NUMPIXELS-(2*i), pixels.Color(150, 150, 0));
          } else {
                pixels.setPixelColor(NUMPIXELS-(2*i), pixels.Color(0, 150, 0));
            }
      }
    }
    pixels.show();
    delay(5);
 }