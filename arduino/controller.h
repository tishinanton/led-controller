#include "FastLED.h"

#define LED_COUNT 110

#define LED_DT 9

struct LedController
{

    int sCmd, sRed, sGreen, sBlue, sLed, sBrightness, sMode;
    int cRed, cGreen, cBlue, cColorStep;
    struct CRGB leds[LED_COUNT];
    int brightness = 255;
    int mode = 0;
    int modeStep = 0;

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
        Serial.println("4 - Set mode (mode: 0 - 1)");
    }

    void setBrightness(int brightness)
    {
        this->brightness = brightness;
        LEDS.setBrightness(brightness);
    }

    void setColor(int red, int green, int blue)
    {
        // this->cRed = red;
        // this->cGreen = green;
        // this->cBlue = blue;
        for (int i = 0; i < LED_COUNT; i++)
        {
            this->setLedColor(i, red, green, blue);
        }
    }

    void setLedColor(int led, int red, int green, int blue)
    {
        this->leds[led].setRGB(red, green, blue);
    }

    void setMode(int mode)
    {
        this->mode = mode;
        switch (this->mode)
        {
        case 0:
            this->setColor(0, 255, 0);
            break;
        case 1:
            this->prepareRunningMode();
            break;
        case 2:
            this->prepareRunningColorMode();
            break;
        }
    }

    void prepareRunningColorMode()
    {
        this->setColor(255, 0, 0);
        this->cRed = 255;
        this->cGreen = 0;
        this->cBlue = 0;
        this->cColorStep = 1;
        this->modeStep = 0;
    }

    void prepareRunningMode()
    {
        this->setColor(0, 0, 0);
        this->modeStep = 0;
    }

    void nextStep()
    {

        switch (this->mode)
        {
        case 0:
            return;
        case 1:
            this->nextRunningStep();
            break;
        case 2:
            this->nextRunningColorStep();
            break;
        }
    }

    void nextRunningStep()
    {

        int offset = LED_COUNT - this->modeStep;
        this->setColor(0, 0, 0);
        for (int i = 0; i < 30; i++)
        {
            int j = offset + i;
            if (j >= LED_COUNT)
            {
                j -= LED_COUNT;
            }
            this->setLedColor(j, this->cRed, this->cGreen, this->cBlue);
        }
        this->modeStep++;
        this->modeStep = this->modeStep % LED_COUNT;
    }

    void nextRunningColorStep()
    {
        switch (this->cColorStep)
        {
        case 1:
            this->cGreen++;
            if (this->cGreen == 255)
            {
                this->cColorStep = 2;
            }
            break;
        case 2:
            this->cRed--;
            if (this->cRed == 0)
            {
                this->cColorStep = 3;
            }
            break;
        case 3:
            this->cBlue++;
            if (this->cBlue == 255)
            {
                this->cColorStep = 4;
            }
            break;
        case 4:
            this->cGreen--;
            if (this->cGreen == 0)
            {
                this->cColorStep = 5;
            }
            break;
        case 5:
            this->cRed++;
            if (this->cRed == 255)
            {
                this->cColorStep = 6;
            }
            break;
        case 6:
            this->cBlue--;
            if (this->cBlue == 0)
            {
                this->cColorStep = 1;
            }
            break;
        }

        int offset = LED_COUNT - this->modeStep;
        this->setColor(0, 0, 0);
        for (int i = 0; i < 30; i++)
        {
            int j = offset + i;
            if (j >= LED_COUNT)
            {
                j -= LED_COUNT;
            }
            this->setLedColor(j, this->cRed, this->cGreen, this->cBlue);
        }
        this->modeStep++;
        this->modeStep = this->modeStep % LED_COUNT;
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

        if (this->sCmd == 4)
        {
            this->sMode = Serial.parseInt();
        }
    }

    void execute()
    {
        switch (this->sCmd)
        {
        case 1:
            Serial.print("Executing: ");
            Serial.print(this->sCmd);
            Serial.print(" red: ");
            Serial.print(this->sRed);
            Serial.print(" green: ");
            Serial.print(this->sGreen);
            Serial.print(" blue: ");
            Serial.println(this->sBlue);
            this->setColor(this->sRed, this->sGreen, this->sBlue);
            break;
        case 2:
            this->setLedColor(this->sLed, this->sRed, this->sGreen, this->sBlue);
            break;
        case 3:
            this->setBrightness(this->sBrightness);
            break;
        case 4:
            this->setMode(this->sMode);
        }
    }
};
