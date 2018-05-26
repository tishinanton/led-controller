/*
  Скетч создан на основе FASTSPI2 EFFECTS EXAMPLES автора teldredge (www.funkboxing.com)
  А также вот этой статьи https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/#cylon
  Доработан, переведён и разбит на файлы 2017 AlexGyver
  Отправляем в монитор порта номер режима, он активируется
*/
// библиотека для работы с лентой
#include "controller.h";

LedController controller;

void setup()
{
    Serial.begin(9600);
    controller.init();
}

void loop()
{
    if (Serial.available() > 0)
    {
        controller.readCommand();
        controller.execute();
    }
    controller.nextStep();
    controller.show();
}