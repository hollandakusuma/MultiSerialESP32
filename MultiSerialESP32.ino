/*
  CHANGE HARDWARE SERIAL IN CPP
  TX2 ESP32 KE TX2 GSM
  TX1 ESP32 KE RX1 GSM
  Serial1.begin() maupun Serial2.begin() langsung tidak bisa digunakan
*/

#include <HardwareSerial.h>
#define s2 // s1 or s2
static const byte RXPin1 = 26, TXPin1 = 27;
HardwareSerial serial1(1);

static const byte RXPin2 = 16, TXPin2 = 17;
HardwareSerial serial2(2);

#ifdef s2
#define SERIAL1 serial2
#endif

#ifdef s1
#define SERIAL1 serial1
#endif

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  delay(1000);
  Serial.println("\r\ntest multiserial ESP32");
#ifdef s2
  SERIAL1.begin(9600, SERIAL_8N1, RXPin2, TXPin2);
  Serial.println("serial2");
#endif

#ifdef s1
  SERIAL1.begin(9600, SERIAL_8N1, RXPin1, TXPin1);
  Serial.println("serial1");
#endif

}

void loop() {
  // read from port 1, send to port 0:
  if (SERIAL1.available()) {
    int inByte = SERIAL1.read();
    Serial.write(inByte);
  }

  // read from port 0, send to port 1:
  if (Serial.available()) {
    int inByte = Serial.read();
    SERIAL1.write(inByte);
  }
}
