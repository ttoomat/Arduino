/* Date: 17.04.2026 
 * Purpose: Lamp + relay + IR LED control project.
 */ 
#define IR_RECEIVE_PIN A0 // analog pin!
#include <IRremote.h> // 4.7.1

uint8_t relay_in1 = 2;
uint8_t relay_in2 = 3;
uint8_t buzzer_pin = 4;

void setup() {
  Serial.begin(9600);
  pinMode(relay_in1, OUTPUT);
  pinMode(relay_in2, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

uint8_t relay_state = 0;
uint8_t buzzer_state = 0;
void loop() {
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.decodedRawData == 0xF30CBB44) {
      relay_state = (relay_state + 1) % 2;
      if (relay_state) {
        digitalWrite(relay_in1, HIGH); // Выключаем реле
        digitalWrite(relay_in2, HIGH); // Выключаем реле
      } else {
        digitalWrite(relay_in1, LOW);  // Включаем реле
        digitalWrite(relay_in2, LOW);  // Включаем реле
      }
    } else {
      if (IrReceiver.decodedIRData.decodedRawData == 0xEE11BB44) {
        buzzer_state = (buzzer_state + 1) % 2;
        if (buzzer_state) {
          digitalWrite(buzzer_pin, HIGH); // Выключаем пищалку
        } else {
          digitalWrite(buzzer_pin, LOW);  // Включаем пищалку
        }
      }
    }
    IrReceiver.resume();
  }
}
