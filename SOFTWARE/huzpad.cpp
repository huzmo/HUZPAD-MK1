
#include "huzpad.h"
#include <HID-Project.h>
#include <HID-Settings.h>
#include <Arduino.h>

macropad::macropad(){
  String user_settings[19] = 
  {
    "macro", 
    "N/A", 
    "pot", 
    " ", 
    "app", 
    "url", 
    "url", 
    "app", 
    "url", 
    "spotify",
    "''",
    "''",
    "''",
    "''", 
    "''", 
    "D2L", 
    "YOUTUBE",
    "''",
    "REDDIT"
  };
  
  switch_A = 10;                                      
  switch_B = 16;
  switch_C = 14;
  switch_D = 15;
  switch_E = 18;
  pot_A = 10;
  Serial.begin(9600);
  pinMode(switch_A, INPUT_PULLUP);
  pinMode(switch_B, INPUT_PULLUP);
  pinMode(switch_C, INPUT_PULLUP);
  pinMode(switch_D, INPUT_PULLUP);
  pinMode(switch_E, INPUT_PULLUP);
  pinMode(pot_A, INPUT_PULLUP);

  Consumer.begin();
  Keyboard.begin();
  delay(1000);

  for(int a = 0; a < 52; a++) {
    Consumer.write(MEDIA_VOLUME_DOWN);
    delay(2);
  }
}

void macropad::change_volume(){
  int current_value = 0;
  int previous_value = 0;
  int new_value = 0;
  int counter = 0;
  current_value = analogRead(A1);
  current_value = map(current_value, 0, 1023, 0, 101);
  if(abs(current_value - previous_value) > 1) {
    previous_value = current_value;
    current_value /= 2;
    while(new_value < current_value) {
      Consumer.write(MEDIA_VOLUME_UP);
      new_value++;
      counter = counter + 0.2;
      delay(2);
    }
    while(new_value > current_value) {
      Consumer.write(MEDIA_VOLUME_DOWN);
      new_value--;
      counter = counter - 0.2;
      delay(2);
    }
  }
  delay(301);   
}

void macropad::macro(int key_num){
  
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.releaseAll();
  if(user_settings[key_num + 4] == "app"){
    for(auto x : user_settings[key_num + 9])
    {
      Keyboard.press(x);
      Keyboard.releaseAll();
    }
    delay(200);
    Keyboard.press(0x0A);
    Keyboard.releaseAll();
    delay(500);
  }
  else if(user_settings[key_num + 4] == "url"){
    for(auto x : "GOOGLE")
    {
      Keyboard.press(x);
      Keyboard.releaseAll();
    }
    delay(200);
    Keyboard.press(0x0A);
    Keyboard.releaseAll();
    delay(200);
    for(auto x : user_settings[key_num + 14])
    {
      Keyboard.press(x);
      Keyboard.releaseAll();
    }
    delay(200);
  Keyboard.press(0x0A);
  Keyboard.releaseAll();
  delay(500);
  }
}

void macropad::read_input(){
  if (digitalRead(switch_A) == LOW) // Macro 1 OPEN SPOTIFY
  {
    macro(0);
  }

  if (digitalRead(switch_B) == LOW) // Macro 2 OPEN YOUTUBE
  {
    macro(1);
  }

  if (digitalRead(switch_C) == LOW) // Macro 3 OPEN D2L
  {
    macro(2);
  }

  if (digitalRead(switch_D) == LOW) // Macro 4 CHANGE AUDIO OUTPUT
  {
    macro(3);
  }

  if (digitalRead(switch_E) == LOW) // change potentiometer setting and display setting string on oled
  {
    macro(4);
  }

  change_volume();
}
