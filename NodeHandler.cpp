#include "NodeHandler.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include "RF24/RPi/RF24/nRF24L01.h"
#include "RF24/RPi/RF24/RF24.h"
#include "RF24/RPi/RF24/RF24_config.h"
#include <mutex>
#include "SwitchDataPacket.h"

std::mutex NodeAccessMutex;

const uint64_t addresses[2] = { 0xE8E8F0F0E1LL, 0xE8E8F0F0E1LL };

RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);

NodeHandler::NodeHandler()
{

}


NodeHandler::~NodeHandler()
{

}

void NodeHandler::SetWritingPipe(uint64_t pipe)
{
  writingPipe = pipe;
}

//SPI.begin();
void NodeHandler::InitRadio()
{
  SetWritingPipe(addresses[1]);
  // Refer to RF24.h or nRF24L01 DS for settings
  radio.begin();

  radio.setDataRate(RF24_1MBPS); //parameters: RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps
  radio.setPALevel(RF24_PA_MAX); //sets Ppwer Amp: RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM, and RF24_PA_HIGH=0dBm.
  radio.setRetries(5,15);
  radio.setAutoAck(true);
  radio.setCRCLength(RF24_CRC_16);
  radio.openWritingPipe(writingPipe);
  radio.openReadingPipe(1,addresses[2]);
  radio.startListening();
  radio.printDetails();

}

bool NodeHandler::WriteData(DataPacket *pack, int size)
{
  bool returnVal;

  NodeAccessMutex.lock();
  radio.openWritingPipe(writingPipe);
  radio.stopListening();

  returnVal = radio.write( pack, sizeof(pack));
  NodeAccessMutex.unlock();
  return returnVal;
}
