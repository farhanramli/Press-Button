/*
 * press_button.cpp
 *
 *  Created on: Feb 14, 2018
 *      Author: farhan r
 */
 
#include "press_button.h"
#include "Arduino.h"

SuperButton::SuperButton(int pin):_pin(pin)
{
	this->_state = BTN_IDLE;
}

uint8_t SuperButton::check(PRESS_BUTTON_STATE &check_state, uint8_t &response)
{
	uint8_t status = 0;
	this->_action = check_state;
	switch(this->_state)
	{
	case BTN_IDLE:
		if(response == 1)
		{
			this->_state = BTN_BOUNCE;
			this->_last_debounce = millis();

		}
		//else do nothing
		break;
	case BTN_BOUNCE:
		if(response == 1)
		{
			if(millis() - this->_last_debounce < (unsigned long) this->_debounce_time)
				break;
			this->_state = BTN_PRESSED;
			if(this->_action == BTN_PRESSED)
				status = 1;
		}
		else
		{
			this->_state = BTN_IDLE;
		}
		break;

	case BTN_PRESSED:
		if(response == !(1))
		{
			this->_state = BTN_BOUNCE2;
			this->_last_debounce = millis();
		}
		//else do nothing
		break;

	case BTN_BOUNCE2:
		if(response == !(1))
		{
			if(millis() - this->_last_debounce < (unsigned long) this->_debounce_time)
				break;
			this->_state = BTN_RELEASED;
		}
		else
		{
			this->_state = BTN_PRESSED;
		}
		break;

	case BTN_RELEASED:
		if(this->_action == BTN_RELEASED)
			status = 1;
		if(response == !(1))
			this->_state = BTN_IDLE;
		break;
	}
	// end of button
	
	return status;
}

PressButton::PressButton(int pin):SuperButton(pin)
{
	this->_debounce_time = 5;
	this->_active = 0;
	pinMode(this->_pin, INPUT);
	
}
PressButton::PressButton(int pin, BUTTON_ACTIVE active):SuperButton(pin), _active(active)
{
	this->_debounce_time = 5;
	pinMode(this->_pin, INPUT);
}

PressButton::PressButton(int pin, BUTTON_ACTIVE active, int debounce_time):SuperButton(pin),_active(active)
{
	this->_debounce_time = debounce_time;
	pinMode(this->_pin, INPUT);
}

int PressButton::checkState(PRESS_BUTTON_STATE check_state)
{
	uint8_t tmpReadBit = (uint8_t)digitalRead(this->_pin);
	uint8_t response;
	if(tmpReadBit == this->_active)
		response = 1;
	else
		response = 0;
		
	return (int)this->check(check_state, response);
}

PressButtonAnalog::PressButtonAnalog(int pin, int val):SuperButton(pin), _val(val)
{
	this->_debounce_time = 5;
	this->_tolerance = 10;
}

PressButtonAnalog::PressButtonAnalog(int pin, int val, int debounce_time):
SuperButton(pin), _val(val)
{
	this->_debounce_time = debounce_time;
	this->_tolerance = 10;
}

void PressButtonAnalog::changeTolerance(int tolerance)
{
	this->_tolerance = tolerance;
}

int PressButtonAnalog::_last_analog_pin = 0;
int PressButtonAnalog::_last_analog_read = 0;
unsigned long PressButtonAnalog::_last_conversion_time = 0;

int PressButtonAnalog::checkState(PRESS_BUTTON_STATE check_state)
{
	int tmpRead;
	if((this->_last_analog_pin == this->_pin) && (this->_last_conversion_time == millis()))
	{
		tmpRead = this->_last_analog_read;
	}
	else
	{
		tmpRead = analogRead(this->_pin);
		this->_last_analog_read = tmpRead;
		this->_last_analog_pin = this->_pin;
		this->_last_conversion_time = millis();
	}
	
	int min = this->_val - this->_tolerance;
	int max = this->_val + this->_tolerance;
	uint8_t response;
	if((tmpRead > min) && (tmpRead < max))
		response = 1;
	else
		response = 0;
	
	return (int)this->check(check_state, response);
}


