/* Press Button
 * 
 * Toggle LED when press button has been released.
 * Pin 13 as LED.
 * Pin 2 as press button.
 * Pull up on pin 2. Resistor may range from 2k to 10k.
 * Press button is HIGH on idle and LOW on active. (Active-LOW)
 * 
 * There are 2 way to declare a button, which
 * 1st example: assign input pin and adc value
 * 2nd example: 1st ex. + assign debounce time (milisecond)
 * 
 * There are also a method(void) to change tolerance of adc value. default is 10.
 *
 */

#include <press_button.h>

int led_state;
PressButtonAnalog button1(A0, 330);
//PressButtonAnalog button1(A0, 330,20);	//(pin, adc_value, debounce)


void setup() {
  // put your setup code here, to run once:
  
  button1.changeTolerance(5);	//change tolerance for adc_value to +- 5
  led_state = LOW;
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
  Serial.begin(9600);
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
