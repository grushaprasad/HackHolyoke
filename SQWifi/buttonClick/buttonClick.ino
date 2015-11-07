#include <Adafruit_NeoPixel.h>

#define PIN_LED       2
#define PIN_BUZZER    15
#define PIN_BUTTON    0

// create pixel object
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
  
  pixel.begin();  // initialize neopixel
  pixel.show();

  pinMode(PIN_BUZZER, OUTPUT);  // set buzzer pin to output mode
  
  pinMode(PIN_BUTTON, INPUT_PULLUP); // set button to input with internal pullup
  
}

void loop() {

  if(digitalRead(PIN_BUTTON)==LOW) {
    int r = random(0,64);
    int g = random(0,64);
    int b = random(0,64);
    pixel.setPixelColor(0, pixel.Color(r, g, b));
    pixel.show();
    int freq = random(220,2200);
    playNote(freq, 200);
  }

}

void playNote(int freq, int delaytime) {
  if(freq>0) {
    analogWrite(PIN_BUZZER, 512);
    analogWriteFreq(freq);
  } else {
    analogWrite(PIN_BUZZER, 0);
  }
  yield_delay(delaytime);
  analogWrite(PIN_BUZZER, 0);
}

void yield_delay(long ms) {
  unsigned long t = millis();
  while(millis()<t+ms) yield();
}
