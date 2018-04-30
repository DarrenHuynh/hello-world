byte b;
#include <SoftwareSerial.h> 

SoftwareSerial MySerial(0, 1);

// Buffer to store incoming commands from serial port
String inData;

void setup() {
    Serial.begin(9600);  
    MySerial.begin(9600);
    Serial.println("Waiting for teensy to send a signal...\n");
}

void loop() {
    while (MySerial.available() > 0)
    {
        char recieved = MySerial.read();
        inData += recieved; 

        // Process message when new line character is recieved
        if (recieved == '\n')
        {
            Serial.print("Arduino Received: ");
            Serial.print(inData);

            inData = ""; // Clear recieved buffer
        }
    }
}





