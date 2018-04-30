/***************************************
 This shows all the wakeups for hibernate
 Expect IDD of  around 15uA (Teensy 3.x)
 and IDD of around 6uA for (Teensy LC).
 
 Hibernate puts the USB regualtor into
 a low power state which will effect
 Teensy 3.0/3.1/LC 3.3v output or
 anything that uses the regualtor.
 ****************************************/
#include <Snooze.h>
// Load drivers
SnoozeDigital digital;
int led = 13;
/***********************************************************
 Teensy 3.6/LC can't use Timer Driver with either Touch or
 Compare Drivers and Touch can't be used with Compare.
 
 Teensy 3.5 does not touch interface.
 
 Teensy LC does not have a rtc so Alarm driver can't be
 used as of yet.
 
 Teensy 3.2 can use any Core Drivers together.
 ***********************************************************/
SnoozeBlock config_teensy32(digital);


void setup() {
    pinMode(led, OUTPUT);
    /********************************************************
     Define digital pins for waking the teensy up. This
     combines pinMode and attachInterrupt in one function.
     
     Teensy 3.x
     Digtal pins: 2,4,6,7,9,10,11,13,16,21,22,26,30,33
     
     Teensy LC
     Digtal pins: 2,6,7,9,10,11,16,21,22
     ********************************************************/
    digital.pinMode(22, INPUT_PULLDOWN, HIGH);//pin, mode, type
   
    
}

void loop() {
    int who;
    /********************************************************
     feed the sleep function its wakeup parameters. Then go
     to hibernate.
     ********************************************************/
    who = Snooze.hibernate( config_teensy32 );// return module that woke processor

    
    if (who == 22) { // pin wakeup source is its pin value
        for (int i = 0; i < 1; i++) {
            digitalWrite(led, HIGH);
            delay(200);
            digitalWrite(led, LOW);
            delay(200);
        }
    }
    
}
