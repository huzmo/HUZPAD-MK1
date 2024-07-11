#ifndef HUZPAD_H
#define HUZPAD_H
#include <Arduino.h>
class macropad {
public:
  macropad();
  void change_volume();
  void macro(int key_num);
  void read_input();

private:
  String user_settings[19];
  int switch_A;                                      
  int switch_B;
  int switch_C;
  int switch_D;
  int switch_E;
  int pot_A;
};

#endif
