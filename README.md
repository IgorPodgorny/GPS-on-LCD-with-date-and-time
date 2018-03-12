# GPS-on-LCD-with-date-and-time
Show GPS coordinates, current date and time on 2 lines 1602 LCD
Модифицированный код из примера: https://eax.me/arduino-gps/https://eax.me/arduino-gps/
Поочерёдно показывает на LCD координаты, время, дату
Используется библиотеки: SoftwareSerial.h для создания SoftSerial = программный COM, он же Serial-port, чтобы получать данные с GPS
LiquidCrystal_I2C.h для LCD-дисплея
TinyGPS++.h для модуля GPS
