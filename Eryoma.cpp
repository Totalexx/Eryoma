/*
 * Eryoma.cpp
 * 
 * Written by Popov Vitaliy(https://vk.com/vitaliy1279)
 *
 * https://eryoma.info
 *
 * https://vk.com/roboekb
 *
 * https://vk.com/eryoma_info
 *
 * Version 5.2 
 */

#ifndef Eryoma_cpp
#define Eryoma_cpp

#include "Eryoma.h"

Eryoma::Eryoma(){
	//motor D
	pinMode(34, OUTPUT);
	pinMode(33, OUTPUT);
	pinMode(10, OUTPUT);
	//motor C
	pinMode(36, OUTPUT);
	pinMode(35, OUTPUT);
	pinMode(9,  OUTPUT);
	//motor B
	pinMode(39, OUTPUT);
	pinMode(40, OUTPUT);
	pinMode(4,  OUTPUT);
	//motor A
	pinMode(37, OUTPUT);
	pinMode(38, OUTPUT);
	pinMode(5,  OUTPUT);
}

int16_t Eryoma::setupConnector(int16_t connector, uint8_t sensor){
	if(connector > -1 && connector < 8){
		switch(sensor){
			case Ultrasonic:
				pinMode(connectorPins[connector][1],INPUT);
				pinMode(connectorPins[connector][0],OUTPUT);
			break;
			case LineArray:
			case TrafficLight:
			case DoubleSegment:
				pinMode(connectorPins[connector][0], OUTPUT);
				pinMode(connectorPins[connector][1], OUTPUT);
				pinMode(connectorPins[connector][2], OUTPUT);
				pinMode(connectorPins[connector][3], INPUT);
			break;	
			case Keypad:
				pinMode(connectorPins[connector][0], INPUT);
				pinMode(connectorPins[connector][1], INPUT);
				pinMode(connectorPins[connector][2], INPUT);
				pinMode(connectorPins[connector][3], INPUT);	
			break;
			case Microphone:
				pinMode(connectorPins[connector][3], INPUT);
			break;
			default:
				Serial.println("ERROR setupConnector. Invalid module.");
				return -1;
			break;	
		}
		Sensors[connector] = sensor;
		return 1;
	}else{
		Serial.println("ERROR setupConnector. Invalid connector.");
		return -2;
	}
}

int16_t Eryoma::getPin(int16_t connector, int16_t pin){
	if(connector > -1 && connector < 8){
		return connectorPins[connector][pin];
	}else{
		Serial.println("ERROR getPin. Invalid connector.");
		return -2;
	}
}

int16_t Eryoma::read(int16_t connector){
	if(connector > -1 && connector < 8){
		switch(Sensors[connector]){
			case Ultrasonic:
				digitalWrite(connectorPins[connector][0], 1);
				delayMicroseconds(10);
				digitalWrite(connectorPins[connector][0], 0);
				return pulseIn(connectorPins[connector][1], HIGH)/58;
			break;
			case Microphone:
			case TrafficLight:
				return analogRead(connectorPins[connector][3]);
			break;
			default:
				Serial.println("ERROR read. Invalid sensor.");
				return -1;
			break;		
		}
	}else{
		Serial.println("ERROR read. Invalid connector.");
		return -2;
	}
}

int16_t Eryoma::read(int16_t connector, int16_t pin){
	if(connector > -1 && connector < 8){
		switch(Sensors[connector]){
			case LineArray:
				digitalWrite(connectorPins[connector][2], bitRead(pin, 0));
				digitalWrite(connectorPins[connector][1], bitRead(pin, 1));
				digitalWrite(connectorPins[connector][0], bitRead(pin, 2));
				return analogRead(connectorPins[connector][3]);
			break;
			case Keypad:
				if(pin != 3){
					return digitalRead(connectorPins[connector][pin]);
				}else{
					return analogRead(connectorPins[connector][3]);
				}
			break;
			default:
				Serial.println("ERROR read. Invalid sensor.");
				return -1;
			break;
		}
	}else{
		Serial.println("ERROR read. Invalid connector.");
		return -2; 
	}
}

int16_t Eryoma::write(int16_t connector, int16_t pin){
	if(connector > -1 && connector < 8){
		switch(Sensors[connector]){
			case DoubleSegment:
				if (pin < 100 && pin > -1) {
					digitalWrite(connectorPins[connector][1], LOW);
					shiftOut(connectorPins[connector][0], connectorPins[connector][2], MSBFIRST, number_DS[(byte)pin / 10]);
					shiftOut(connectorPins[connector][0], connectorPins[connector][2], MSBFIRST, (number_DS[(byte)pin % 10]>>4)|(number_DS[(byte)pin % 10]<<4));
					digitalWrite(connectorPins[connector][1], HIGH);
				} else {
					digitalWrite(connectorPins[connector][1], LOW);
					shiftOut(connectorPins[connector][0], connectorPins[connector][2], MSBFIRST, number_DS[10]);
					shiftOut(connectorPins[connector][0], connectorPins[connector][2], MSBFIRST, number_DS[10]<<4);
					digitalWrite(connectorPins[connector][1], HIGH);
				}
				
			break;
			default:
				Serial.println("ERROR write. Invalid sensor.");
				return -1;
			break;
		}
		return 1;		
	}else{
		Serial.println("ERROR read. Invalid connector.");
		return -2;
	}
}

double Eryoma::write(int16_t connector, double pin){
	if(connector > -1 && connector < 8){
		switch(Sensors[connector]){
			case DoubleSegment:
				if (pin < 10 && pin >= 0) {
					byte number = pin * 10;
					digitalWrite(connectorPins[connector][1], LOW);
					shiftOut(connectorPins[connector][0], connectorPins[connector][2], MSBFIRST, number_DS[number / 10] | 0b00010000);
					shiftOut(connectorPins[connector][0], connectorPins[connector][2], MSBFIRST, (number_DS[number % 10]>>4)|(number_DS[number % 10]<<4));
					digitalWrite(connectorPins[connector][1], HIGH);
				} else {
					digitalWrite(connectorPins[connector][1], LOW);
					shiftOut(connectorPins[connector][0], connectorPins[connector][2], MSBFIRST, number_DS[10]);
					shiftOut(connectorPins[connector][0], connectorPins[connector][2], MSBFIRST, number_DS[10]);
					digitalWrite(connectorPins[connector][1], HIGH);
				}
			break;
			default:
				Serial.println("ERROR write. Invalid sensor.");
				return -1;
			break;
		}
		return 1;
	}else{
		Serial.println("ERROR read. Invalid connector.");
		return -2;
	}
}

int16_t Eryoma::write(int16_t connector, int16_t pinD0, int16_t pinD1){
	if(connector > -1 && connector < 8){
		switch(Sensors[connector]){
			case DoubleSegment:		
				digitalWrite(connectorPins[connector][1], LOW);
				shiftOut(connectorPins[connector][0], connectorPins[connector][2], MSBFIRST, pinD0);
				shiftOut(connectorPins[connector][0], connectorPins[connector][2], MSBFIRST, pinD1);
				digitalWrite(connectorPins[connector][1], HIGH);
			break;
			default:
				Serial.println("ERROR write. Invalid sensor.");
				return -1;
			break;	
		}
		return 1;
	}else{
		Serial.println("ERROR read. Invalid connector.");
		return -2;
	}
	
}

int16_t Eryoma::write(int16_t connector, int16_t pinD0, int16_t pinD1, int16_t pinD2){
	if(connector > -1 && connector < 8){
		switch(Sensors[connector]){
			case TrafficLight:		
				analogWrite(connectorPins[connector][1], pinD0);
				analogWrite(connectorPins[connector][0], pinD1);
				analogWrite(connectorPins[connector][2], pinD2);
			break;
			default:
				Serial.println("ERROR write. Invalid sensor.");
				return -1;
			break;	
		}
		return 1;
	}else{
		Serial.println("ERROR read. Invalid connector.");
		return -2;
	}
	
}
int16_t Eryoma::setMotorSpeed(int16_t motor, int16_t motorspeed){
	if(motorspeed > 0){
		switch(motor){
			case A:
				analogWrite(5, motorspeed);
				digitalWrite(37, LOW);
				digitalWrite(38, HIGH);
			break;
			case B:
				analogWrite(4, motorspeed);
				digitalWrite(39, LOW);
				digitalWrite(40, HIGH);
			break;
			case C:
				analogWrite(9, motorspeed);
				digitalWrite(35, LOW);
				digitalWrite(36, HIGH);
			break;
			case D:
				analogWrite(10, motorspeed);
				digitalWrite(33, LOW);
				digitalWrite(34, HIGH);
			break;
			default:
				Serial.println("ERROR setMotorSpeed. Invalid port.");
				return -1;
			break;
		}
		return 1;
	}else{
		switch(motor){
			case A:
				analogWrite(5, abs(motorspeed));
				digitalWrite(37, HIGH);
				digitalWrite(38, LOW);
			break;
			case B:
				analogWrite(4, abs(motorspeed));
				digitalWrite(39, HIGH);
				digitalWrite(40, LOW);
			break;
			case C:
				analogWrite(9, abs(motorspeed));
				digitalWrite(35, HIGH);
				digitalWrite(36, LOW);
			break;
			case D:
				analogWrite(10, abs(motorspeed));
				digitalWrite(33, HIGH);
				digitalWrite(34, LOW);
			break;
			default:
				Serial.println("ERROR setMotorSpeed. Invalid port.");
				return -1;
			break;
		}
		return 1;
	}
}

#endif 