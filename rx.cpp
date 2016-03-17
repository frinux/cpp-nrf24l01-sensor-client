/**
 * Simplest possible example of using RF24Network,
 *
 * RECEIVER NODE
 * Listens for messages from the transmitter and prints them out.
 */

#include <RF24/RF24.h>
#include <RF24Network/RF24Network.h>
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <time.h>


// CE Pin, CSN Pin, SPI Speed
RF24 radio(RPI_BPLUS_GPIO_J8_15,RPI_BPLUS_GPIO_J8_24, BCM2835_SPI_SPEED_8MHZ);


RF24Network network(radio);

// Address of our node in Octal format
const uint16_t this_node = 00;

const int channel = 90;

struct payload_t {
  unsigned long ms;
  float humidity; // %
  float temperature; // celcius
};

int main(int argc, char** argv) 
{
	radio.begin();
	
	delay(5);
	network.begin(channel, this_node);
	radio.printDetails();
	
	while(1)
	{

		  network.update();
  		  while ( network.available() ) {
    			
		 	RF24NetworkHeader header;
   			payload_t payload;
  			network.read(header,&payload,sizeof(payload));

  			 //TODO
  			 //payload.ms
  			 //payload.humidity
  			 //payload.temperature
			
			//printf("Received payload # %lu at %lu \n",payload.counter,payload.ms);
			printf("Received payload at %lu : %f°C, %f percent\n",payload.ms, payload.temperature, payload.humidity);
  		}		  

		 delay(2000);
	}

	return 0;
}
