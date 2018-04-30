#define MySerial Serial1

void setup() {

MySerial.begin(9600);


}


void loop() {
String b ="hello\n";
MySerial.print(b);


delay(2000);
}

