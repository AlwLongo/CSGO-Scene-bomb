#ifndef PASSWORD_SCREEN_H
#define PASSWORD_SCREEN_H
    #include "globals.h"
    
    #define PASS_MAX_LEN 8
    #define PASS_MIN_LEN 4
    
    class PasswordScreen
    {
    private:
        String buffer;

    public:
        PasswordScreen() : buffer(""){};

        String start(){
            bool passOK = 0;
            int command;
            char input;
            int len = 0;
            while (!passOK)
            {
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Scegli Password:");
                lcd.setCursor(0,1);
                lcd.print(buffer);
                
                do
                {
                    command = read_LCD_buttons();
                    if (command == btnNONE)
                    {
                        input = keypad.getKey();
                        if(input != NO_KEY){
                            buffer += input;
                            len ++;
                
                            lcd.clear();
                            lcd.setCursor(0,0);
                            lcd.print("Scegli Password:");
                            lcd.setCursor(0,1);
                            lcd.print(buffer);
                            delay(200);
                        }
                    }
                    else if(command == btnLEFT){ 
                        buffer.remove(len--);    
                        
                        lcd.clear();
                        lcd.setCursor(0,0);
                        lcd.print("Scegli Password:");
                        lcd.setCursor(0,1);
                        lcd.print(buffer);
                        delay(200);
                    }
                }
                while(command != btnSELECT);

                if (len >= PASS_MIN_LEN && len <= PASS_MAX_LEN)
                    passOK = 1;
                else
                    bad_password_screen(&len);
            }

            return buffer;
        }

        void bad_password_screen(int* len_pass){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("   PASSWORD   ");
            lcd.setCursor(0,1);
            if (*len_pass > PASS_MAX_LEN)
                lcd.print(" TROPPO LUNGA ");
            if (*len_pass < PASS_MIN_LEN)
                lcd.print(" TROPPO CORTA ");

            delay(2000);
            buffer = "";
            *len_pass = buffer.length();
        };
    };
    
#endif