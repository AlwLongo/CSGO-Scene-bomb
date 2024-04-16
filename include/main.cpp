
//Sample using LiquidCrystal library
#include "globals.h"
#include "timer_screen.h"
#include "password_screen.h"
#include "game.h"

void loose_screen();
void win_screen();


/*******************************************************

This program will test the LCD panel and the buttons on D1 Robot LCD Keypad
Michael Jonathan, February 2019

********************************************************/

// define some values used by the panel and buttons

//NOTHING..

//


bool end_game(){
  if (started_game.ended)
  {
    if(started_game.disarmed)
      win_screen();
    
    loose_screen();
  }
  return 0;
}

bool refresh_game(){
  started_game.refresh_screen();

  return true;
}

bool input_deamon(){
  started_game.input_deamon();
  return true;
}


void setup()
{
  lcd.begin(16, 2);              // start the library
  lcd.setCursor(0, 1);
  lcd.print("UXENTUM BOMB");
  lcd.setCursor(0,1);
  lcd.print("Made By A.L");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  
  clock = first_screen.start();
  started_game.game_time = &clock;

  password = second_screen.start();
  started_game.Password = &password;

  timer.at(clock.in_millis(), end_game);
  timer.every(SECOND, refresh_game);
  timer.every(INPUT_CHECK, input_deamon);
}

void loop()
{
  started_game.start();
  timer.tick();
  
}



// Lcd_fast_print_function
void win_screen(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BOMBA Disarm.");
  lcd.setCursor(0, 1);
  lcd.print("premi SELECT");
}


