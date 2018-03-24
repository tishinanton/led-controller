#include "FastLED.h"

#define LED_COUNT 19
#define LED_DT 6

struct LedController
{

    int sCmd, sRed, sGreen, sBlue, sLed, sBrightness;

    struct CRGB leds[LED_COUNT];
    int brightness = 255;

    void init()
    {
        LEDS.addLeds<WS2811, LED_DT, GRB>(this->leds, LED_COUNT);
        this->setColor(0, 0, 0);
        this->show();

        this->printCommands();
    }

    void printCommands()
    {
        Serial.println("1 - Set color of strip (red: 0 - 255, green: 0 - 255, blue: 0 - 255)");
        Serial.print("2 - Set color of led (red: 0 - 255, green: 0 - 255, blue: 0 - 255, led: 0 - ");
        Serial.print(LED_COUNT);
        Serial.println(")");
        Serial.println("3 - Set brightness (brightness: 0 - 255)");
    }

    void setBrightness(int brightness)
    {
        this->brightness = brightness;
        LEDS.setBrightness(brightness);
    }

    void setColor(int red, int green, int blue)
    {
        for (int i = 0; i < LED_COUNT; i++)
        {
            this->setLedColor(i, red, green, blue);
        }
    }

    void setLedColor(int led, int red, int green, int blue)
    {
        this->leds[led].setRGB(red, green, blue);
    }

    void show()
    {
        LEDS.show();
    }

    void readCommand()
    {
        this->sCmd = Serial.parseInt();
        if (this->sCmd == 1 || this->sCmd == 2)
        {
            this->sRed = Serial.parseInt();
            this->sGreen = Serial.parseInt();
            this->sBlue = Serial.parseInt();
        }
        if (this->sCmd == 2)
        {
            this->sLed = Serial.parseInt();
        }

        if (this->sCmd == 3)
        {
            this->sBrightness = Serial.parseInt();
        }
    }

    void execute()
    {
        switch (this->sCmd)
        {
        case 1:
            this->setColor(this->sRed, this->sGreen, this->sBlue);
            break;
        case 2:
            this->setLedColor(this->sLed, this->sRed, this->sGreen, this->sBlue);
            break;
        case 3:
            this->setBrightness(this->sBrightness);
            break;
        }
    }
};
