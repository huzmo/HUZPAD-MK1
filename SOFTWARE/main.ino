#include "huzpad.h"

int main(){
  macropad my_device;
  while(1)
    my_device.read_input();
  return 0;
}
