#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"
#include <printf.h>

int _input1 = 7;
int SentMessage[1] = {000};
RF24 radio(9, 10);
const uint64_t pipe = 0xe9e9e9e9e9LL;

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
  delay(1000);
}

void loop(void) {
  if (digitalRead(_input1)) {
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
  if (_result){
    Serial.print("Send Completed.\n\r");
    delay(5000);
  }
  else
    Serial.print("Send Failed.\n\r");
}

