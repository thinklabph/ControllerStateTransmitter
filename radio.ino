/*
 * See documentation at https://nRF24.github.io/RF24
 * See License information at root directory of this library
 * Author: Brendan Doherty (2bndy5)
 */

/**
 * A simple example of sending data from 1 nRF24L01 transceiver to another.
 *
 * This example was written to be used on 2 devices acting as "nodes".
 * Use the Serial Monitor to change each node's behavior.
 */
#include <SPI.h>
#include "printf.h"
#include "RF24.h"

#define CE_PIN 7
#define CSN_PIN 6

// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);

uint8_t address[][6] = { RF24_ADDRESS, RF24_ADDRESS };

uint64_t payload = 0;

void initRadio(uint64_t payload){

  // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}  // hold in infinite loop
  }
  else Serial.println(F("Radio OK!"));

  // Set the PA Level low to try preventing power supply related problems
  // because these examples are likely run with nodes in close proximity to
  // each other.
  radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.

  // save on transmission time by setting the radio to only transmit the
  // number of bytes we need to transmit a float
  radio.setPayloadSize(sizeof(payload));  // float datatype occupies 4 bytes

  // set the TX address of the RX node into the TX pipe
  radio.openWritingPipe(address[0]);  // always uses pipe 0
  // radio.openWritingPipe(MY_ADDRESS);  // always uses pipe 0

  // set the RX address of the TX node into a RX pipe
  radio.openReadingPipe(1, address[1]);  // using pipe 1

  radio.stopListening();  // put radio in TX mode
  
}  // setup

void radioTransmit(uint64_t payload) {

  unsigned long start_timer = micros();  
  bool report = radio.write(&payload, sizeof(uint64_t));  // transmit & save the report
  unsigned long end_timer = micros();    
  
  if (report) {
    // Serial.print(F("Transmission successful! "));  // payload was delivered
    // Serial.print(F("Time to transmit = "));
    // Serial.print(end_timer - start_timer);  // print the timer result
    Serial.println(F("Sent"));
    // Serial.println(payload);  // print payload sent
    // payload += 0.01;          // increment float payload
  } else {
    Serial.println(F("Fail"));  // payload was not delivered
  } 

}  // loop
