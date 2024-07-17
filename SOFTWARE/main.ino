#include "huzpad.h"

void setup() { }

void loop() {
  macropad my_device;
  while(1)
    my_device.read_input();
}
