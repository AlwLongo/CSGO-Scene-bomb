#ifndef TIMER_SCREEN_H
#define TIMER_SCREEN_H

#include "globals.h"

class TimerScreen {
public:
    Time clock;
    int selectedField;
    int readyToClose;

    TimerScreen() : clock(), selectedField(1), readyToClose(0) {}

    void selectorToRight() {
        if (selectedField < FIELDS)
            selectedField++;
        else
            selectedField = 1;
    }

    void selectorToLeft() {
        if (selectedField > 1)
            selectedField--;
        else
            selectedField = FIELDS;
    }

    void interact(int action) {
        switch (action) {
        case btnDOWN:
            clock.leaveForField(selectedField);
            break;

        case btnUP:
            clock.addForField(selectedField);
            break;

        case btnLEFT:
            selectorToLeft();
            break;

        case btnRIGHT:
            selectorToRight();
            break;

        case btnSELECT:
            readyToClose = 1;
            break;

        default:
            break;
        }
    }

    void printTimerScreen(int blink) {
        lcd.setCursor(0, 0);
        lcd.print("Imposta timer:");
        lcd.setCursor(0, 1);
        String timerString;
        timerString = "";  // Initialize with two spaces

        if (selectedField == HOURS && blink)
            timerString += "  H:";
        else
            timerString += this->clock.fieldToString(HOURS) + "H:";

        if (selectedField == MINUTES && blink)
            timerString += "  M:";
        else
            timerString += this->clock.fieldToString(MINUTES) + "M:";

        if (selectedField == SECONDS && blink)
            timerString += "  S";
        else
            timerString += this->clock.fieldToString(SECONDS)+ "S";

        lcd.print(timerString);
    }

    Time start() {
        int input;
        int blinkFlag = 0;
        
        while (!readyToClose) {
            lcd.clear();
            printTimerScreen(blinkFlag);

            input = read_LCD_buttons();
            if (input != btnNONE) {
                interact(input);
            }

            blinkFlag = !blinkFlag;
            delay(300);
        }

        return this->clock;
    }
};

#endif
