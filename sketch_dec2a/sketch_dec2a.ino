#include "Adafruit_NeoPixel.h" // подключаем библиотеку

#define LED_STRING_PIN  12 // указываем пин для подключения ленты
#define SKIPLEDS 10        // первые столько светодиодов торчат и должны быть выключены
#define NUMPIXELS 84       // указываем количество светодиодов в ленте
#define LED_delay 50       // насколько плавно бежит строка - пока не учитываем
#define MICRO_PIN1 A2      // пин микрофона
#define MICRO_PIN2 A4      // пин микрофона 

// создаем объект strip с нужными характеристиками
Adafruit_NeoPixel strip (NUMPIXELS, LED_STRING_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
   Serial.begin(115200);
   analogReference(EXTERNAL); // опорное напряжение для микрофона
   strip.begin();             // инициализируем ленту
   strip.setBrightness(10);   // указываем яркость светодиодов (максимум 255)
}

int isRed = 1, changed=0; // флаги для переключения света
uint32_t red_color = strip.Color(255, 55, 200); // при превышении включается он
uint32_t green_color = strip.Color(157, 77, 219);
uint32_t current_color = green_color;
void loop() {
   if (analogRead(MICRO_PIN1) > 700) {
      // просто меняем цвет при превышении
      changed=1;
      isRed = !isRed;
   } else {
      changed=0;
   }

   if (changed) {
      if (isRed) {
         current_color = red_color;
      } else {
         current_color = green_color;
      }
      for (int i=0; i < (NUMPIXELS-SKIPLEDS)/2; i++) {
         // расходятся из серединки
         strip.setPixelColor((SKIPLEDS+NUMPIXELS)/2+i, current_color);
         strip.setPixelColor((SKIPLEDS+NUMPIXELS)/2-i, current_color);
         strip.show();   // отправляем сигнал на ленту
         delay(LED_delay);
      }
   }
   Serial.println(analogRead(MICRO_PIN1));
}
