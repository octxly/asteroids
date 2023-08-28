#ifndef LEDCTRL
#define LEDCTRL

#include <Arduino.h>

#define STARTLIVES 3
#define LED_BRIGHT_ANALOG_OUT 15

#define MED_PULSE_SPD 2
#define LOW_PULSE_SPD 0.5

class LEDControl{
    private:
        uint8_t ledPin;

    public:
        uint8_t lives = STARTLIVES;

        LEDControl(uint8_t ledPin) : ledPin(ledPin) {
            pinMode(ledPin, OUTPUT);
        }

        void update(){
            switch (lives){
                case 3:
                    analogWrite(ledPin, LED_BRIGHT_ANALOG_OUT);
                break;

                case 2:
                    analogWrite(ledPin, 0.5f * (1.0f + sin(2.0f * PI * millis() / (MED_PULSE_SPD * 1000.0f))) * LED_BRIGHT_ANALOG_OUT);
                    // analogWrite(ledPin, LED_BRIGHT_ANALOG_OUT / 8);
                break;

                case 1:
                    analogWrite(ledPin, 0.5f * (1.0f + sin(2.0f * PI * millis() / (LOW_PULSE_SPD * 1000.0f))) * LED_BRIGHT_ANALOG_OUT);
                break;

                default:
                    analogWrite(ledPin, 0);
                break;
            }
        }
};

#endif