#ifndef TIME_CONCEPT_H
    #define TIME_CONCEPT_H
    #include "globals.h"


#define FIELDS 3
#define HOURS 1
#define MINUTES 2
#define SECONDS 3

#define MEDIUM_BLINK 500
#define INPUT_CHECK  75
#define SECOND  1000


class Time {
private:
    int ore;
    int minuti;
    int secondi;
    


    unsigned long starting_point;
    bool isRunning;

public:
    bool ended;

    Time(){
            ore = 0;
            minuti = 1;
            secondi = 30;
            isRunning =false;
            ended = false;
        };

    int addHour() {
        if (ore < 24) {
            ore++;
            return 1;
        }
        return 0;
    }

    int leaveHour() {
        if (ore > 0) {
            ore--;
            return 1;
        }
        return 0;
    }

    int addMinute() {
        if (minuti < 59) {
            minuti++;
            return 1;
        } else {
            if (addHour()) {
                minuti = 0;
                return 1;
            }
            return 0;
        }
    }

    int leaveMinute() {
        if (minuti > 0) {
            minuti--;
            return 1;
        } else {
            if (leaveHour()) {
                minuti = 59;
                return 1;
            }
            return 0;
        }
    }

    int addSecond() {
        if (secondi < 59) {
            secondi++;
            return 1;
        } else {
            if (addMinute()) {
                secondi = 0;
                return 1;
            }
            return 0;
        }
    }

    bool leaveSecond() {
        if (secondi > 0) {
            secondi--;
            if(isRunning)
                return true;
            
            return true;
        } else if (leaveMinute()) {
            secondi = 59;
            return 1;
        }else if(isRunning){
            ended = true;
        }

        return 0;
    }

    int leaveForField(int field) {
        int feedback;
        switch (field) {
        case HOURS:
            feedback = leaveHour();
            break;

        case MINUTES:
            feedback = leaveMinute();
            break;

        case SECONDS:
            feedback = leaveSecond();
            break;
        }

        return feedback;
    }

    int addForField(int field) {
        int feedback;
        switch (field) {
        case HOURS:
            feedback = addHour();
            break;

        case MINUTES:
            feedback = addMinute();
            break;

        case SECONDS:
            feedback = addSecond();
            break;
        }

        return feedback;
    }

    String printFormatted(int value) {
        String s_value;
        if (value < 10) {
            s_value = "0" + String(value);
        } else {
            s_value = String(value);
        }

        return s_value;
    }

    String fieldToString(int field = -1) {
        String result;
        switch (field) {
        case HOURS:
            result = printFormatted(ore);
            break;

        case MINUTES:
            result = printFormatted(minuti);
            break;

        case SECONDS:
            result = printFormatted(secondi);
            break;
        
        default:
            result = to_string();
            break;
        }
       
        return result;
    }

    String to_string(){
        String clock="";
        clock += fieldToString(HOURS)+"H ";
        clock += fieldToString(MINUTES)+"M ";
        clock += fieldToString(SECONDS)+"S";
        return clock;
    }
    
    unsigned long in_millis() const {
        return static_cast<long>(ore) * 3600000 + static_cast<long>(minuti) * 60000 + static_cast<long>(secondi) * 1000;
    }

    unsigned long in_micros() const {
        return static_cast<long>(ore) * 3600000000 + static_cast<long>(minuti) * 60000000 + static_cast<long>(secondi) * 1000000;
    }

    void start(){
        isRunning = 1; 
    }

    bool is_on_last_ten_seconds(){
        if(in_millis() < 10000)
                return 1;

        return 0;
    }

    bool is_on_last_minute(){
        if(in_millis() < 60000)
            return 1;

        return 0;
    }

    bool is_ended(){
        return ended;
    }

};

#endif
