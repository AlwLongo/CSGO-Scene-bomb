#ifndef GAME_H
#define GAME_H
#include "globals.h"

enum DANGER_STATUS{ STARTED , OK, ON_LAST_MINUTE, ON_LAST_TEN_SECONDS, ENDED};

class Game {
    
private:    
    

public:
    Time *game_time;

    String* Password;
    String P_buffer;

    DANGER_STATUS actual_status;
    DANGER_STATUS on_refresh_status;

    bool started;
    bool ended;
    bool disarmed;

    bool on_last_ten_seconds = 0;
    bool on_last_minute = 0;

    int on_bad_password_screen_delay,
    attemps_remaining;

    int command;
    char input;



    Game(Time* choosen_game_time, String* choosen_password) {
        this->game_time = choosen_game_time;
        this->Password = choosen_password;
        
        command = btnNONE;
        input = NO_KEY;
        P_buffer = "";

        attemps_remaining = 3;
        on_bad_password_screen_delay = 0;
        
        started = false;
        disarmed = false;
        ended = false;
        actual_status = STARTED;
    }


    void wrong_password_screen(){
        on_bad_password_screen_delay = 2;
        if (attemps_remaining > 1)
        {            
            attemps_remaining--;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("WRONG PASSWORD");
            lcd.setCursor(0,1);
            lcd.print("attemps r. =");
            lcd.print(attemps_remaining);
            P_buffer = "";
        }else{
            ended = true;
            is_win();
        } 
    }

    bool refresh_screen(bool on_buffer_change = false) {
        if (started && !ended)
        {
            update_danger_status();
            if(on_bad_password_screen_delay == 0){
                lcd.clear();
                lcd.setCursor(0, 0);
                String timerString;
                timerString = "";  // Initialize with two spaces
                timerString += game_time->fieldToString(HOURS) + "H:";
                timerString += game_time->fieldToString(MINUTES) + "M:";
                timerString += game_time->fieldToString(SECONDS)+ "S";
                lcd.print(timerString);

                lcd.setCursor(0,1);
                lcd.print("passw:");
                lcd.print(P_buffer);
            }else
                on_bad_password_screen_delay --;
        }
        
        if (!on_buffer_change)
            if(!game_time->leaveSecond()){
                ended = 1;
                is_win();
            }
                
        return 1;
    }

    bool input_deamon() {
        command = read_LCD_buttons();

        if(started && !ended){   
            if (command == btnNONE) {
                input = keypad.getKey();
                if (input != NO_KEY){ 
                    P_buffer.concat(input);

                    Serial.print("AGGIUNTO CARATTERE: ");
                    Serial.println(input);
                    refresh_screen(1);
                }

            } else if (command == btnLEFT) {
                P_buffer.remove(P_buffer.length() - 1);

                Serial.print("AGGIUNTO CARATTERE: ");
                Serial.println(input);
                refresh_screen(1);  
            } else if (command == btnSELECT) {
                if (*Password == P_buffer){
                    disarmed = 1;
                    ended = 1;
                    is_win();
                }else{
                    wrong_password_screen();
                }
            }

        }else if(disarmed || ended){
            while(1){
                if(command == btnSELECT);
                
                command = read_LCD_buttons();
                delay(75);
            }
        }
        
        return 1;
    }

    void start(){
        game_time->start();
        started = true;
    }

    void is_win(){
        if (ended)
        {
            if(disarmed){
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("DISARMATA");
                lcd.setCursor(0, 1);
                lcd.print("premi RST");
                
                //GOING TO REBOOT
                input_deamon();
            }else{
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("BOOOM!");
                lcd.setCursor(0, 1);
                lcd.print("premi RST");
                
                
                //GOING TO REBOOT
                input_deamon();
            }
        }

    }

    void get_stat(){
        Serial.println("#############  STAT  #############");
        Serial.print(disarmed);
        Serial.println(" DISARMATA");

        Serial.print(started); 
        Serial.println(" AVVIATA");

        Serial.print(ended);
        Serial.println(" FINITA");
    }
    
    DANGER_STATUS update_danger_status(){
        if (!on_last_minute && !game_time->is_on_last_minute()){
            return OK;
        }else if(!on_last_ten_seconds && !game_time->is_on_last_ten_seconds()){
            return ON_LAST_MINUTE;
        }else if(!game_time->ended && !game_time->is_ended()){
            return ON_LAST_TEN_SECONDS;
        }else
            return ENDED;
    }

    bool is_status_updated(){
        on_refresh_status = update_danger_status();
        if (on_refresh_status != actual_status)
        {
            actual_status = on_refresh_status;
            return false;
        }

        return true;
    }

    DANGER_STATUS get_danger_level(){
        return actual_status;
    }
};

#endif