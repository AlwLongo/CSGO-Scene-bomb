/*
 Test timer rollover handling
 */



#include <util/atomic.h>
#include <arduino-timer.h>

#include "globals.h"
#include "timer_screen.h"
#include "password_screen.h"
#include "game.h"

#include <arduino-timer.h>

Timer<5,millis,const char *>::Task blink_task = nullptr;

Time clock;
TimerScreen first_screen;
String password;
PasswordScreen second_screen;
Game started_game(nullptr, nullptr);

/*/*
 * timer_full
 *
 * Full example using the arduino-timer library.
 * Shows:
 *  - Setting a different number of tasks with microsecond resolution
 *  - disabling a repeated function
 *  - running a function after a delay
 *  - cancelling a task
 *
 */


// create a timer that holds 16 tasks, with millisecond resolution,
// and a custom handler type of 'const char *
Timer<5, millis, const char *> buffer_timer;

bool syncronize_timer_and_led(const char *m){

  if(!started_game.is_status_updated()){
    DANGER_STATUS status = started_game.get_danger_level();

    buffer_timer.cancel(blink_task);
    switch (status)
    {
      case ON_LAST_TEN_SECONDS:
          blink_task = buffer_timer.every(200 , toggle_led, "PRETTY_ENDED");
        break;
      case ON_LAST_MINUTE:
           blink_task = buffer_timer.every(500 , toggle_led, "NEAR_TO_END");
        break;
      case OK:
           blink_task = buffer_timer.every(1000 , toggle_led, "NOTHING");
        break;
      case ENDED:
          return 0;
        break;
    }
  }

  return 1;
}

bool refresh_screen(const char *m) {
    started_game.get_stat();
    started_game.refresh_screen();
    return 1;
}

bool update(const char *m ) {
  started_game.input_deamon();
  return 1;
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(115200);

  lcd.begin(16, 2);              // start the library
  lcd.setCursor(0, 0);
  lcd.print("UXENTUM BOMB");
  lcd.setCursor(0,1);
  lcd.print("Made By A.L");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  
  clock = first_screen.start();
  started_game.game_time = &clock;
  delay(100);
    
  password = second_screen.start();
  started_game.Password = &password;
  
  //
  buffer_timer.every(50, syncronize_timer_and_led, "NOPE");

  buffer_timer.every(200, update, "NOPE");
  // call the print_message function every 1000 millis (1 second),
  // passing it an argument string
  buffer_timer.every(1000, refresh_screen, "NOPE");

  // call the toggle_led function every 500 millis (half second)

  // call print_message in 2 seconds, but with microsecond resolution
  //u_timer.in(2000000, , "delayed two seconds using microseconds");
  started_game.start();

  delay(2000);
}

void loop() {
  buffer_timer.tick();
}
