/*
 * TimeRTC.pde
 * example code illustrating Time library with Real Time Clock.
 * 
 */

#include <TimeLib.h>
#include <Snooze.h>
#define MySerial Serial1

SnoozeDigital digital;
int led = 13;

SnoozeBlock config_teensy32(digital);

void setup()  {
  pinMode(led, OUTPUT);
  digital.pinMode(22, INPUT_PULLDOWN, RISING);//pin, mode, type
  digital.pinMode(21, INPUT_PULLDOWN, RISING);//pin, mode, type
  // set the Time library to use Teensy 3.0's RTC to keep time
  setSyncProvider(getTeensy3Time);
  
  MySerial.begin(9600);
  Serial.begin(115200);
  
  //while (!Serial && millis()<4000);  // Wait for Arduino Serial Monitor to open
  delay(100);
  if (timeStatus()!= timeSet) {
    Serial.println("Unable to sync with the RTC");
  } else {
    Serial.println("RTC has set the system time");
  }
  time_t t = 1524077963; //set time; need to change value to correct Epoch time when loading onto teensy
  Teensy3Clock.set(t); // set the RTC
  setTime(t);
}

void loop() {
  
  int who;
  /********************************************************
   feed the sleep function its wakeup parameters. Then go
   to hibernate.
   ********************************************************/
  who = Snooze.hibernate( config_teensy32 );// return module that woke processor
  //transmit serially to RX (pin 0) when input to pin 22 is a rising edge
  if (who == 22) { // pin wakeup source is its pin value
      for (int i = 0; i < 1; i++) {
          digitalClockDisplay();
          digitalWrite(led, HIGH);
          delay(200);
          digitalWrite(led, LOW);
          delay(200);
          setSyncProvider(getTeensy3Time);
          delay(200);
          
      }
  }

   //output to CANBUS if interrupt on pin 21 if it's a rising edge 
   if (who == 21) { // pin wakeup source is its pin value
      for (int i = 0; i < 1; i++) {
        //CANBUS transmit code     
          
      }
  }      
  
  
}

void digitalClockDisplay() {
  // digital clock display of the time output to RX (pin 0)
  MySerial.print(hour());
  MySerial.print(minute());
  MySerial.print(day());
  MySerial.print(month());
  MySerial.print(year());
  MySerial.print("\n"); //newline used to know when reach end of transmission when testing with arduino
  
  /*formatted clock display. Outputs to serial monitor
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  MySerial.print(" ");
  MySerial.print(day());
  MySerial.print(" ");
  MySerial.print(month());
  MySerial.print(" ");
  MySerial.print(year()); 
  */
  
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

/*  code to process time sync messages from the serial port   */
#define TIME_HEADER  "T"   // Header tag for serial time sync message

unsigned long processSyncMessage() {
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     return pctime;
     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
       pctime = 0L; // return 0 to indicate that the time is not valid
     }
  }
  return pctime;
}

//formats time
void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  MySerial.print(":");
  if(digits < 10)
    MySerial.print('0');
  MySerial.print(digits);
}

