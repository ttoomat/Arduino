/* Programmer: Troitskaya Tamara (ttoomat).
 * Board: Arduino Nano.
 * Shows numbers, received from IR remote control.
 * Purpose: for fun.
 * TODO: bigger display to show time or stopwatch.
 */
#include <IRremote.h>

uint8_t IRreceiverPin = A0;
uint8_t displayPin[] = {2, 3, 4, 5, 6, 7, 8, 9}; // A, B, C, D, E, F, G, DP pins
/* Codes of numbers 0-9 */
int num[10][8] = {{1, 1, 1, 1, 1, 1, 0, 1},
  {0, 1, 1, 0, 0, 0, 0, 1}, 
  {1, 1, 0, 1, 1, 0, 1, 1}, 
  {1, 1, 1, 1, 0, 0, 1, 1}, 
  {0, 1, 1, 0, 0, 1, 1, 1}, 
  {1, 0, 1, 1, 0, 1, 1, 1}, 
  {1, 0, 1, 1, 1, 1, 1, 1}, 
  {1, 1, 1, 0, 0, 0, 0, 1}, 
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1, 1}}; 

int N = 8; // number of diaplay segments

/* Turn off all the leds on display.
 */
void turn_off() {
  for (uint8_t pin : displayPin) {
    digitalWrite(pin, LOW);
  }
}

/* Turn on all the leds, marked "1" in the array.
 */
void show(int arr[]) {
  turn_off();
  for (int i = 0; i < N; i++) {
    if (arr[i]) {
      digitalWrite(displayPin[i], HIGH);
    }
  }
}

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IRreceiverPin, ENABLE_LED_FEEDBACK);
  for (uint8_t pin : displayPin)
    pinMode(pin, OUTPUT);
}

void loop() {
  if (IrReceiver.decode()) {
    int i; 
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    switch (IrReceiver.decodedIRData.decodedRawData) {
      case 0xEA15FD00: {
        i = 1;
        break;
      }
      case 0xE916FD00: {
        i = 2;
        break;
      }
      case 0xE817FD00: {
        i = 3;
        break;
      }
      case 0xE619FD00: {
        i = 4;
        break;
      }
      case 0xE51AFD00: {
        i = 5;
        break;
      }
      case 0xE41BFD00: {
        i = 6;
        break;
      }
      case 0xE21DFD00: {
        i = 7;
        break;
      }
      case 0xE11EFD00: {
        i = 8;
        break;
      }
    }
    show(num[i]);
    IrReceiver.resume();
  }
}
