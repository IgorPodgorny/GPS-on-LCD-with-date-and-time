// Модифицированный код из примера: https://eax.me/arduino-gps/https://eax.me/arduino-gps/
// Поочерёдно показывает координаты, время по Гринвичу, дату

//#include <Arduino.h> // подключаем библиотеку со стандартными функциями плат Arduino
#include <SoftwareSerial.h> // подключение библиотеки для создания SoftSerial = программный COM, он же Serial-port. Он нам нужен, чтобы полчать данные с GPS
#include "LiquidCrystal_I2C.h" // подключение библиотеки для LCD-дисплея
#include "TinyGPS++.h" // подключение библиотеки для модуля GPS

const int DELAY = 100;
const int SWITCH_TIME = 1000; // время переключения между отображением даты/времени и координат


LiquidCrystal_I2C lcd (0x27, 4, 5); // 0x27 — адрес экрана на шине I2C. У этого экрана он такой по умолчанию
SoftwareSerial gps_serial(3, 2); // указываем номера пинов, к котором подключены RX, TX
TinyGPSPlus gps_parser; // создаём объект TinyGPSPlus

void setup()
{
  Serial.begin(9600); // инициализируем Serial port

  gps_serial.begin(9600); // инициализируем GPS

  Serial.println("Waiting data of GPS...");

  lcd.begin(16, 2); // указываем размер экрана: 16 символов, 2 строки

  lcd.init();                      // Инициализация дисплея
  lcd.backlight();                 // Подключение подсветки

}

String twoDigits(int x) {
  if (x < 10) return "0" + String(x);
  else return String(x);
}

int currentModeTime = 0;
bool showLocation = false;

void loop() {
  while (gps_serial.available() > 0) {
    char temp = gps_serial.read();
    Serial.write(temp);
    gps_parser.encode(temp);
  }

  String lat  = "Unknown         ";
  String lng  = "location        ";
  if (gps_parser.location.isValid()) {
    lat = "Lat: " + String(gps_parser.location.lat(), 6);
    lng = "Lng: " + String(gps_parser.location.lng(), 6);
  }

  String date = "Unknown date    ";
  if (gps_parser.date.isValid()) {
    date = twoDigits(gps_parser.date.day()) + "/" +
           twoDigits(gps_parser.date.month()) + "/" +
           String(gps_parser.date.year()) + "      ";
  }

  String time = "Unknown time    ";
  if (gps_parser.time.isValid()) {
    time = twoDigits(gps_parser.time.hour() + 3) + ":" +
           twoDigits(gps_parser.time.minute()) + ":" +
           twoDigits(gps_parser.time.second()) + "      ";
  }

  if (showLocation) {
    lcd.setCursor(0, 0);

    lcd.print(lat);
    lcd.print((char)223);

    lcd.setCursor(0, 1);

    lcd.print(lng);
    lcd.print((char)223);

  } else { // show date and time
    lcd.setCursor(0, 0);
    lcd.print(date);
    lcd.setCursor(0, 1);
    lcd.print(time);
  }

  delay(DELAY);
  currentModeTime += DELAY;
  if (currentModeTime >= SWITCH_TIME) {
    lcd.clear();
    showLocation = !showLocation;
    currentModeTime = 0;
  }
}
