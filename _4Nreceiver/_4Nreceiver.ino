#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"
#include <printf.h>

int _output1 = 5;
int _output2 = 6;
int _output3 = 7;
int _output4 = 8;
int ReceivedMessage[1] = {000};
RF24 radio(9, 10);
const uint64_t pipe = 0xebebebebebLL;

void setup(void) {
  Serial.begin(115200);
  printf_begin();
  pinMode(_output1, OUTPUT);
  digitalWrite(_output1, HIGH);
  pinMode(_output2, OUTPUT);
  digitalWrite(_output2, HIGH);
  pinMode(_output3, OUTPUT);
  digitalWrite(_output3, HIGH);
  pinMode(_output4, OUTPUT);
  digitalWrite(_output4, HIGH);
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
    if (ReceivedMessage[0] == 43)
    {
      digitalWrite(_output1, !digitalRead(_output1));
      delay(1500);
    }
    if (ReceivedMessage[0] == 154)
    {
      digitalWrite(_output2, !digitalRead(_output2));
      delay(1500);
    }
    if (ReceivedMessage[0] == 9)
    {
      digitalWrite(_output3, !digitalRead(_output3));
      delay(1500);
    }
    if (ReceivedMessage[0] == 120)
    {
      digitalWrite(_output4, !digitalRead(_output4));
      delay(1500);
    }
  }
}
