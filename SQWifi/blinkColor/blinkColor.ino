#include <Adafruit_NeoPixel.h>

#define PIN_LED     2
#define DELAY_TIME  500

// create pixel object
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
  pixel.begin();  // initialize neopixel
  pixel.show();   // push initial color to neopixel
}

void loop() {
  blinkColor(255, 0, 0);  // blink red

  blinkColor(0, 255, 0);  // blink green

  blinkColor(0, 0, 255);  // blink blue
}

void blinkColor(byte r, byte g, byte b) {
  pixel.setPixelColor(0, pixel.Color(r, g, b)); // set color
  pixel.show(); // push the color to LED
  yield_delay(DELAY_TIME);
  pixel.setPixelColor(0, pixel.Color(0, 0, 0)); // turn off (set color to 0)
  pixel.show();
  yield_delay(DELAY_TIME);
}

// non-blocking delay
// yield() gives processing time to WiFi
void yield_delay(long ms) {
  unsigned long t = millis();
  while(millis()<t+ms) yield();
}

