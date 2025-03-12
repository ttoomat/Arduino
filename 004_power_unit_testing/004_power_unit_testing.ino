/* Программист: Тамара Троицкая @ttoomat
 * Дата создания: 26.02.2025
 * Версия: 3
 * Назначение: для блока питания Колмакова APT 650 DC-DC
 * Плата: Arduino Nano
 * Статус: плата пока не готова, код ещё не был вшит и проверен
 * Алгоритм работы:
    есть 4 пары вход выход. по очереди подаём 0 на вход, на три остальные подаём 5V.
    если на соответствующий выход пришло 5V с драйвера (с драйвера выходит 12V, но у нас стоит понижайка до 5V), то продолжи проверку, иначе ошибка
    загорается зелёный или красный светодиод
    цикл автоматичеки завершается после 1 раза.

    белый светодиод горит = работает цикл
    белый светодиод моргает = можно нажать кнопку для запуска цикла
    кнопка нужна для запуска цикла, после включения она выключена по умолчанию

    Эта версия кода для быстрой тестировки. Для локализации проблемы (1-4 части схемы) она не подходит.
 */

// пины диодов
uint8_t greenLedPin = 2; // диод добра
uint8_t redLedPin = 3; // диод зла
uint8_t whiteLedPin = 4; // диод работы питания и цикла

// пин кнопки
uint8_t buttonPin = A0;

// пины выходов, на которые с ардуино подаём 5V
uint8_t outPin1 = 5;
uint8_t outPin2 = 6;
uint8_t outPin3 = 7;
uint8_t outPin4 = 8;

// пины входов (смотрим, пришло ли 5V)
uint8_t inpPin1 = 9;
uint8_t inpPin2 = 10;
uint8_t inpPin3 = 11;
uint8_t inpPin4 = 12;

// массивы пинов: цветные светодиоды, входы с драйвера, выходы на драйвер
uint8_t leds[] = {greenLedPin, redLedPin};
uint8_t output[] = {outPin1, outPin2, outPin3, outPin4};
uint8_t input[] = {inpPin1, inpPin2, inpPin3, inpPin4};

// нажатие кнопки
bool buttonState = 0;

void whiteLedBlink() {
  digitalWrite(whiteLedPin, LOW);
  delay(200);
  digitalWrite(whiteLedPin, HIGH);
  delay(200);
}

void setup() {
  Serial.begin(9600);
  for (uint8_t led : leds)
    pinMode(led, OUTPUT);
  pinMode(whiteLedPin, OUTPUT);
  for (uint8_t out : output)
    pinMode(out, OUTPUT);
  for (uint8_t inp : input)
    pinMode(inp, INPUT);
  // кнопке нужна подтяжка на питание
  pinMode(buttonPin, INPUT_PULLUP);
}

// прогон для одной пары инпут аутпут
// рекурсивно проверяет все пары
// возвращает 1 если всё верно отработало, 0 если ошибка
bool run(int pair) {
  if (pair >= 4) return 1; // all the 4 worked correctly
  // 5V на все
  for (uint8_t out : output)
    digitalWrite(out, HIGH);
  // 0V на проверяемый
  digitalWrite(output[pair], LOW);
  delay(200);
  if (digitalRead(input[pair]) == HIGH) {
    Serial.print("correct ");
    Serial.println(pair);
    return run(pair + 1);
  } else {
    return 0;
  }
}

void loop() {
  // если кнопка нажата, меняем состояние переменной
  buttonState = (buttonState + !digitalRead(buttonPin)) % 2;
  // если кнопка в состоянии запуска цикла
  if (buttonState) {
    digitalWrite(whiteLedPin, HIGH);
    // тушим все цветные светодиоды
    for (auto led : leds)
      digitalWrite(led, LOW);
    delay(100);
    Serial.println("button = true");
    // вызываем run с парой номер 0 и она рекурсивно проверяет все последующие
    if (run(0)) {
      digitalWrite(greenLedPin, HIGH);
      digitalWrite(redLedPin, LOW);
      Serial.println("ok");
    } else {
      digitalWrite(redLedPin, HIGH);
      digitalWrite(greenLedPin, LOW);
      Serial.println("err");
    }
    delay(100);
    // после 1 прогона цикл останавливается
    buttonState = 0;
  } else {
    // мигание белым светодиодом 1 раз и пошли на новый цикл. пока кнопку не нажмут вот и будет мигать
    whiteLedBlink();
  }
}
