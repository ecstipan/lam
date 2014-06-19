//
//  lwm.h
//  
//
//  Created by Rayce Stipanovich on 5/24/14.
//
//

#ifndef _lwm_h
#define _lwm_h

#include <arduino.h>
#include <lwm_settings.h>

#define LWM _lwm_INITIALIZE()

#ifdef LWM_USE_SOFTWARE_SERIAL
#include <SofrwareSerial.h>
#define lwm_init() _lwm_init_soft()
#define lwm_read() _lwm_read_soft()
#define lwm() SoftwareSerial _lwmS(LWM_RX_PIN, LWM_TX_PIN)
#endif

#ifndef LWM_USE_SOFTWARE_SERIAL
#define lwm_init() _lwm_init()
#define lwm_read() _lwm_read()
#define lwm() 0;
#endif

#define lwm_setup_setial(X) SerialX.begin(31250)

inline void _lwm_init();
inline void _lwm_init_soft();
inline void _lwm_read();
inline void _lwm_read_soft();

void lwm_note_on_callback(byte channel, byte note, byte velocity);
void lwm_note_off_callback(byte channel, byte note);
void lwm_cc_callback(byte channel, byte control, byte value);

#endif
