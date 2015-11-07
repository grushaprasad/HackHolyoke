#include <Adafruit_NeoPixel.h>

#define PIN_LED     2
#define DELAY_TIME  10

// create pixel object
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
  pixel.begin();  // initialize neopixel
  pixel.show();
}

void loop() {
  fadeColor(255, 0, 0);  // fade red

  fadeColor(0, 255, 0);  // fade green
  
  fadeColor(0, 0, 255);  // fade blue
}

void fadeColor(byte r, byte g, byte b) {
  // change color from 0 up to full color value
  for(int i=0;i<100;i++) {
    pixel.setPixelColor(0, pixel.Color(r*i/100, g*i/100, b*i/100));
    pixel.show();
    yield_delay(DELAY_TIME);
  }
  // change color from full color value down to 0
  for(int i=100;i>=0;i--) {
    pixel.setPixelColor(0, pixel.Color(r*i/100, g*i/100, b*i/100));
    pixel.show();
    yield_delay(DELAY_TIME);
  }  
}

// non-blocking delay
// yield() gives processing time to WiFi
void yield_delay(long ms) {
  unsigned long t = millis();
  while(millis()<t+ms) yield();
}

