#include <Arduino.h>
#include "button_check.cpp"

#define BUTTON 7

buttonCheck mb;
uint32_t millisCounter = 0;
uint32_t targetMs = 100;

struct digital_read : buttonCheck_input{
	bool buttonRead(void) override{
		return digitalRead(BUTTON);
	}
};

struct serial_print : buttonCheck_output{
	void printOutput(const char* output) override{
		Serial.println(output);
	}

};

void setup() {
	Serial.begin(9600);
	pinMode(BUTTON, INPUT);
	mb.input = new digital_read;
	mb.output = new serial_print;
	
	millisCounter = millis();
}

void loop() {
	if(millis() - millisCounter >= targetMs){
		millisCounter = millis();
		mb.run();
	}
	
}