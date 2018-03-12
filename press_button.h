/*
 * press_button.h
 *
 *  Created on: Feb 14, 2018
 *      Author: farhan r
 */
 
#ifndef Press_Button_h
#define Press_Button_h

#include "Arduino.h"
#include <inttypes.h>

typedef enum
{
	BTN_IDLE = 0,
	BTN_BOUNCE = 1,
	BTN_PRESSED = 2,
	BTN_BOUNCE2 = 3,
	BTN_RELEASED = 4
}PRESS_BUTTON_STATE;

typedef enum
{
	ACTIVE_LOW = 0,
	ACTIVE_HIGH = 1
}BUTTON_ACTIVE;
		
class PressButton;
class PressButtonAnalog;

class SuperButton
{
	public:
		SuperButton(int pin);
	
	protected:
		const int _pin;
		unsigned int _debounce_time;
		uint8_t check(PRESS_BUTTON_STATE &check_state, uint8_t &response);
		
	private:
		PRESS_BUTTON_STATE _action;
		PRESS_BUTTON_STATE _state;
		unsigned long _last_debounce;
};	
	
class PressButton: protected SuperButton
{
	public:
		PressButton(int pin);
		PressButton(int pin, BUTTON_ACTIVE active);
		PressButton(int pin, BUTTON_ACTIVE active, int debounce_time);
		int checkState(PRESS_BUTTON_STATE check_state);

	private:
		uint8_t _active;
	
};

class PressButtonAnalog: protected SuperButton
{
	public:
		PressButtonAnalog(int pin, int val);
		PressButtonAnalog(int pin, int val, int debounce_time);
		void changeTolerance(int tolerance);
		int checkState(PRESS_BUTTON_STATE check_state);
	
	private:
		int _tolerance;
		int _val;
		static int _last_analog_pin;
		static int _last_analog_read;
		static unsigned long _last_conversion_time;
};



#endif /* Press_Button_h */
