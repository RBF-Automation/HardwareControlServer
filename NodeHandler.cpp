#include "NodeHandler.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "RF24/RPi/RF24/nRF24L01.h"
#include "RF24/RPi/RF24/RF24.h"
#include "RF24/RPi/RF24/RF24_config.h"


const uint64_t addresses[2] = { 0xE8E8F0F0E1LL, 0xE8E8F0F0E1LL };

RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);

NodeHandler::NodeHandler()
{

}


NodeHandler::~NodeHandler()
{

}



//SPI.begin();
void NodeHandler::InitRadio()
{
  // Refer to RF24.h or nRF24L01 DS for settings
  radio.begin();

  radio.setDataRate(RF24_1MBPS); //parameters: RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps
  radio.setPALevel(RF24_PA_MAX); //sets Ppwer Amp: RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM, and RF24_PA_HIGH=0dBm.
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[2]);
  radio.startListening();
  radio.printDetails();

}

void NodeHandler::WriteData(int data)
{
  radio.stopListening();
  radio.write( &data, sizeof(data) );
}
