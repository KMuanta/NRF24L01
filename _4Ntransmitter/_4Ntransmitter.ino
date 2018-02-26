#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"
#include <printf.h>

int _input1 = 5;
int _input2 = 6;
int _input3 = 7;
int _input4 = 8;
int SentMessage[1] = {000};
RF24 radio(9, 10);
const uint64_t pipe = 0xebebebebebLL;

void setup(void) {
  Serial.begin(115200);
  printf_begin();
  radio.begin();
  radio.openWritingPipe(pipe);
  radio.setDataRate(RF24_1MBPS);
  radio.setChannel(0x4d);
  radio.stopListening();
  radio.printDetails();
  pinMode(_input1, INPUT);
  pinMode(_input2, INPUT);
  pinMode(_input3, INPUT);
  pinMode(_input4, INPUT);
  delay(1000);
}

void loop(void) {
  if (digitalRead(_input1) && !digitalRead(_input2) && !digitalRead(_input3) && !digitalRead(_input4)) {
    send(555);
  }
  if (!digitalRead(_input1) && digitalRead(_input2) && !digitalRead(_input3) && !digitalRead(_input4)) {
    send(666);
  }
  if (!digitalRead(_input1) && !digitalRead(_input2) && digitalRead(_input3) && !digitalRead(_input4)) {
    send(777);
  }
  if (!digitalRead(_input1) && !digitalRead(_input2) && !digitalRead(_input3) && digitalRead(_input4)) {
    send(888);
  }
  delay(10);
}

void send(int __input) {
  Serial.println(__input);
  SentMessage[0] = __input;
  bool _result;
  _result = radio.write(SentMessage, 1);
  Serial.print(_result);
  if (_result)
    Serial.print("Send Completed.\n\r");
  else
    Serial.print("Send Failed.\n\r");
    delay(3000);
}

