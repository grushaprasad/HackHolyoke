#include "pitches.h"

#define PIN_BUZZER    15

// these notes are macro defines in pitches.h
// they correspond to the frequency of each note
int melody[] = {
  NOTE_G3, NOTE_C4,NOTE_E4, NOTE_G4, NOTE_E4, NOTE_G4
};

// 4 = quarter note, 8 = eighth note, etc.:
int duration[] = {
  4, 8, 8, 4, 8, 2
};

void setup() {
  
  pinMode(PIN_BUZZER, OUTPUT);
  
  // iterate over the notes of the melody:
  for (int i = 0; i < sizeof(melody)/sizeof(int); i++) {
    int delaytime = 1000/duration[i];
    playNote(melody[i], delaytime);
    
    // add 30% pause between notes
    int pausetime = delaytime * 0.3;
    playNote(0, pausetime);
  }
}

void loop() {
  // generate a random note with frequency
  // between 220Hz and 2.2kHz
  int freq = random(220, 2200);

  // generate a random duration
  // between 100ms to 0.5s
  int duration = random(50, 200);

  playNote(freq, duration);
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
