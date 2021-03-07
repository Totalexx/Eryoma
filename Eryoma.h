/*
 * Eryoma.h
 * 
 * Written by Vitaliy Popov(https://vk.com/vitaliy1279)
 *
 * https://eryoma.info
 *
 * https://vk.com/roboekb
 *
 * https://vk.com/eryoma_info
 *
 * Version 5.2
 */

#ifndef Eryoma_h
#define Eryoma_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 

class Eryoma{
	public:
		Eryoma();
		
		//buttons IR remote
		#define BUTTON_CH_MINUS 0xFFA25D
		#define BUTTON_CH 0xFF629D
		#define BUTTON_CH_PLUS 0xFFE21D
		#define BUTTON_PREV 0xFF22D0
		#define BUTTON_NEXT 0xFF02FD
		#define BUTTON_PLAY_PAUSE 0xFFC23D
		#define BUTTON_VOL_MINUS 0xFFE01F
		#define BUTTON_VOL_PLUS 0xFF02FD
		#define BUTTON_EQ 0xFF906F
		#define BUTTON_0 0xFF6897
		#define BUTTON_100 0xFF9867
		#define BUTTON_200 0xFFB04F
		#define BUTTON_1 0xFF30CF
		#define BUTTON_2 0xFF18E7
		#define BUTTON_3 0xFF7485
		#define BUTTON_4 0xFF10EF
		#define BUTTON_5 0xFF38C7
		#define BUTTON_6 0xFF5AA5
		#define BUTTON_7 0xFF42BD
		#define BUTTON_8 0xFF4AB5
		#define BUTTON_9 0xFF52AD
		#define BUTTON_HOLD 0xFFFFFF
		
		//connectors
		#define ePort0			0
		#define ePort1			1
		#define ePort2			2
		#define ePort3			3
		#define ePort4			4
		#define ePort5			5
		#define ePort6			6
		#define ePort7			7
		
		//pins
		#define D0 				0
		#define D1 				1
		#define D2 				2
		#define An 				3
		
		//modules
		
		#define Ultrasonic 		11
		#define TrafficLight 	12
		#define Keypad 			13
		#define Touch 			13
		#define TiltSensor		13
		#define LineArray 		14
		#define DoubleSegment 	15
		#define Microphone		16	
		
		//motors
		
		#define A 				255
		#define B 				254
		#define C 				253
		#define D 				252
		
		//metods
		
		int16_t getPin(int16_t connector, int16_t pin);
		int16_t	setupConnector(int16_t connector, uint8_t sensor);
		int16_t	read(int16_t connector);
		int16_t	read(int16_t connector, int16_t pin);
		int16_t	write(int16_t connector, int16_t pin);
		double 	write(int16_t connector, double pin);
		int16_t	write(int16_t connector, int16_t pinD0, int16_t pinD1);
		int16_t	write(int16_t connector, int16_t pinD0, int16_t pinD1, int16_t pinD2);
		int16_t	setMotorSpeed(int16_t motor, int16_t motorspeed);
		
		
	private:	
		int16_t	Sensors[8] = {0, 0, 0, 0, 0, 0, 0, 0};
		int16_t	connectorPins[8][4] = {{43, 42, 41, 58},{46, 45, 44, 59},{49, 48, 47, 60},{52, 51, 50, 61},{19, 20, 21, 57},{16, 17, 18, 56},{8, 7, 6, 55},{13, 12, 11, 54}};
		int16_t	number_DS[11] = {0b11101110, 0b00101000, 0b11001101, 0b01101101, 0b00101011, 0b01100111, 0b11100111, 0b00101100, 0b11101111, 0b01101111, 0b00000001};
};

#endif