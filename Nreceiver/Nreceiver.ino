#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"
#include <printf.h>

int _output1 = 7;
int ReceivedMessage[1] = {0};
RF24 radio(9, 10);
const uint64_t pipe = 0xe9e9e9e9e9LL;

void setup(void) {
  pinMode(_output1, OUTPUT);
  digitalWrite(_output1, LOW);
  Serial.begin(115200);
  printf_begin();
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.setDataRate(RF24_1MBPS);
  radio.setChannel(0x4d);
  radio.startListening();
  radio.printDetails();
  delay(1000);
}

void loop(void) {
  while (radio.available()) {    
    radio.read(ReceivedMessage, 1);
    Serial.println(ReceivedMessage[0]);
    if (ReceivedMessage[0] == 120)
    {
      digitalWrite(_output1, !digitalRead(_output1));
      ReceivedMessage[0] = 0;
      delay(5000);
    }
  }
}
