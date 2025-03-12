/* Programmer: Troitskaya Tamara (ttoomat).
 * Board: Arduino Nano.
 * Buzzes when water is detected.
 * Purpose: to avoid flooding at home.
 * TODO: case.
 */
uint8_t waterPin = A6; // water sensor pin
uint8_t piezoPin = 4;
int waterLevel;

void setup()
{
  pinMode(waterPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  waterLevel = analogRead(waterPin); // water level: 0-1023
    if (waterLevel > 350) {
      tone(piezoPin, 1000, 500);
    }
  Serial.println(waterLevel);
  delay(1000);
}
