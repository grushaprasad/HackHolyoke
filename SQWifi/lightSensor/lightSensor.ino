#include <Adafruit_NeoPixel.h>

#define PIN_LED     2
#define PIN_LIGHTSENSOR_ENABLE  16
#define PIN_LIGHTSENSOR A0

// create pixel object
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
  pixel.begin();  // initialize neopixel
  pixel.show();
  pinMode(PIN_LIGHTSENSOR_ENABLE, OUTPUT);
  digitalWrite(PIN_LIGHTSENSOR_ENABLE, HIGH);
  Serial.begin(115200);
}

void loop() {
  int light_value = analogRead(PIN_LIGHTSENSOR);
  Serial.println(light_value);
  pixel.setPixelColor(0, pixel.Color(0, 0, (1024-light_value)/4));
  pixel.show();
  yield_delay(200);
}

// non-blocking delay
// yield() gives processing time to WiFi
void yield_delay(long ms) {
  unsigned long t = millis();
  while(millis()<t+ms) yield();
}

