#ifndef TIMER_SCREEN_H
#define TIMER_SCREEN_H

#include "globals.h"

class end_screen{
public:
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

    void start() {
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
