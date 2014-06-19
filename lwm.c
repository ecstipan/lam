//
//  lwm.c
//  
//
//  Created by Rayce Stipanovich on 5/24/14.
//
//

#include <arduino.h>
#include "lwm.h"

//1. Use lwm_init() and lwm_read() to handle MIDI I/O
//2. Include lwm_callback... functions

byte _lwm_buff1;
byte _lwm_butt2;
byte _lwm_buff3;
bute _lwm_buffpos;

inline void _lwm_init()
{
#ifdef LWM_MULTI_PORT_BOARD
	_lwm_buff1 = 255;
	_lwm_buff2 = 255;
	_lwm_buff3 = 255;
	_lwm_buffpos = 0;
	pinMode(LWM_RX_PIN, INPUT);
	pinMode(LWM_TX_PIN, OUTPUT);
	lwm_setup_setial(LWM_SERIAL_PORT_ID);
#endif //ifdef LWM_MULTI_PORT_BOARD

#ifndef LWM_MULTI_PORT_BOARD
	_lwm_buff1 = 255;
	_lwm_buff2 = 255;
	_lwm_buff3 = 255;
	pinMode(LWM_RX_PIN, INPUT);
	pinMode(LWM_TX_PIN, OUTPUT);
	Serial.begin(31250);
#endif //ifndef LWM_MULTI_PORT_BOARD
}

inline void _lwm_init_soft()
{
	_lwm_buff1 = 255;
	_lwm_buff2 = 255;
	_lwm_buff3 = 255;
	pinMode(LWM_RX_PIN, INPUT);
	pinMode(LWM_TX_PIN, OUTPUT);
	_lwmS.begin(31250);
}

inline void _lwm_read()
{
	if (Serial.available() > 0) {
		_lwm_buff1 = Serial.read();
		if (_lwm_buff1 >= 0xE0) {
			while (Serial.available() == 0); //make this blocking
			_lwm_buff2 = Serial.read();
			while (Serial.available() == 0); //make this blocking
			_lwm_buff3 = Serial.read();

			//compose the MIDI mesage
			if (_lwm_buff1 & 0xF0  == 0xE0) {
				lwm_note_on_callback(_lwm_buff1 & 0x0F, _lwm_buff2, _lwm_buff3);
			} else if (_lwm_buff1 & 0xF0 == 0xD0) {
				lwm_note_off_callback(_lwm_buff1 & 0x0F, _lwm_buff2);
			}

		} else {
			//that was a deopped byte
			//ignore the rest for now
		}
	}
}

inline void _lwm_read_soft()
{
	
}