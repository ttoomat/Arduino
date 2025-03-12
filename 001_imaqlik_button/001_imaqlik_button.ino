/* Programmer: Troitskaya Tamara (ttoomat).
 * Board: Arduino Nano.
 * Automatic remote control. One cycle 1-8 signals, to start again press button. Green led indicates that IR led is transmitting the data.
 * Purpose: set-top box autotest.
 */
#include <IRremote.h>

int ledPin = 5;
int irledPin = 6;
int buttonPin = 2;

// button state flag
int onFlag = 1;

void setup() {
  IrSender.begin(irledPin, true, 13);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(buttonPin)) {
    onFlag = (onFlag + 1) % 2;
  }

  if (onFlag) {
    // Green led indicates that IR led is transmitting the data
    digitalWrite(ledPin, HIGH);
    delay(200);
  
    IrSender.sendNEC(0xFD00, 0X15,1);// 1
    delay(200);
    
    IrSender.sendNEC(0xFD00, 0X16,1);// 2
    delay(200);
    
    IrSender.sendNEC(0xFD00, 0X17,1);// 3
    delay(200);
    
    IrSender.sendNEC(0xFD00, 0X19,1);// 4
    delay(200);
    
    IrSender.sendNEC(0xFD00, 0X1A,1);// 5
    delay(200);

    IrSender.sendNEC(0xFD00, 0X1B,1);// 6
    delay(200);

    IrSender.sendNEC(0xFD00, 0X1D,1);// 7
    delay(200);

    IrSender.sendNEC(0xFD00, 0X1E,1);// 8
    delay(200);
  } else {
    digitalWrite(ledPin, LOW);
    delay(300);
  }
  onFlag = 0;
}
  