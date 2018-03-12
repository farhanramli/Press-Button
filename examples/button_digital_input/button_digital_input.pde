/* Press Button
 * 
 * Toggle LED when press button has been released.
 * Pin 13 as LED.
 * Pin 2 as press button.
 * button condition is HIGH on idle and LOW on active. (ACTIVE_LOW)
 * Pull up on pin 2. Resistor may range from 2k to 10k.
 * for internal pull-up, can add line below in setup()
 *    pinMode(pin, INPUT_PULLUP); //enable internal pull-up
 * 
 * There are 3 way to declare a button, which
 * 1st example: assign input pin only (default ACTIVE_LOW & 10ms debounce)
 * 2nd example: 1st example + assign button active direction (ACTIVE_LOW or ACTIVE_HIGH)
 * 3rd example: 2nd example + assign debounce time (milisecond)
 * 
 */

#include <press_button.h>

int led_state;
PressButton button1(2);
//PressButton button1(2, ACTIVE_LOW);
//PressButton button1(2, ACTIVE_LOW, 20);	//(pin, direction, debounce) 


void setup() {
  // put your setup code here, to run once:
  led_state = LOW;
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int r = button1.checkState(BTN_RELEASED);
  if(r)
  {
    if(led_state)
      led_state = LOW;
    else
      led_state = HIGH;
      
    digitalWrite(13, led_state);
  }

}
