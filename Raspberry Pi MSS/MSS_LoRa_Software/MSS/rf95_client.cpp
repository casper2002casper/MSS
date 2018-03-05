// rf95_client.cpp
//
// Example program showing how to use RH_RF95 on Raspberry Pi
// Uses the bcm2835 library to access the GPIO pins to drive the RFM95 module
// Requires bcm2835 library to be already installed
// http://www.airspayce.com/mikem/bcm2835/
// Use the Makefile in this directory:
// cd example/raspi/rf95
// make
// sudo ./rf95_client
//
// Contributed by Charles-Henri Hallard based on sample RH_NRF24 by Mike Poublon

#include <bcm2835.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <RH_RF69.h>
#include <RH_RF95.h>
#include <cstring>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
// define hardware used change to fit your need
// Uncomment the board you have, if not listed
// uncommment custom board and set wiring tin custom section

// LoRasPi board
// see https://github.com/hallard/LoRasPI
//define BOARD_LORASPI

// iC880A and LinkLab Lora Gateway Shield (if RF module plugged into)
// see https://github.com/ch2i/iC880A-Raspberry-PI
//#define BOARD_IC880A_PLATE

// Raspberri PI Lora Gateway for multiple modules
// see https://github.com/hallard/RPI-Lora-Gateway
//#define BOARD_PI_LORA_GATEWAY


// Dragino Raspberry PI hat
// see https://github.com/dragino/Lora
#define BOARD_DRAGINO_PIHAT

// Now we include RasPi_Boards.h so this will expose defined
// constants with CS/IRQ/RESET/on board LED pins definition
#include "RadioHead/examples/raspi/RasPiBoards.h"

// Our RFM95 Configuration
#define RF_FREQUENCY  868.00
#define RF_GATEWAY_ID 1
#define RF_NODE_ID    10

#define SENDSPEED 2500
#define RECEIVESPEED 1000

//Define csv filename with measurement data:
#define FILENAME "/media/mss/MSS_USB2/measurements/measurement.csv"
#define FILENAME_TEMP "/media/mss/MSS_USB2/measurements/measurement_temp.csv"

// Create an instance of a driver
RH_RF95 rf95(RF_CS_PIN, RF_IRQ_PIN);
//RH_RF95 rf95(RF_CS_PIN);

//Flag for Ctrl-C
volatile sig_atomic_t force_exit = false;

void sig_handler(int sig)
{
  printf("\n%s Break received, exiting!\n", __BASEFILE__);
  force_exit=true;
}

//Main Function
int main (int argc, const char* argv[] )
{
	static unsigned long last_millis;
	static unsigned long led_blink = 0;
	uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
	
	//create boolean saved to check if packet is saved
	bool saved = false;
	int packet_nr = 0;
	char message_id[3];
	char packet_nr_send[3];
	
	signal(SIGINT, sig_handler);
	printf( "%s\n", __BASEFILE__);

	if (!bcm2835_init()) {
	fprintf( stderr, "%s bcm2835_init() Failed\n\n", __BASEFILE__ );
	return 1;
	}

	printf( "RF95 CS=GPIO%d", RF_CS_PIN);

	#ifdef RF_LED_PIN
	pinMode(RF_LED_PIN, OUTPUT);
	digitalWrite(RF_LED_PIN, HIGH );
	#endif

	#ifdef RF_IRQ_PIN
	printf( ", IRQ=GPIO%d", RF_IRQ_PIN );
	// IRQ Pin input/pull down
	pinMode(RF_IRQ_PIN, INPUT);
	bcm2835_gpio_set_pud(RF_IRQ_PIN, BCM2835_GPIO_PUD_DOWN);
	#endif

	#ifdef RF_RST_PIN
	printf( ", RST=GPIO%d", RF_RST_PIN );
	// Pulse a reset on module
	pinMode(RF_RST_PIN, OUTPUT);
	digitalWrite(RF_RST_PIN, LOW );
	bcm2835_delay(150);
	digitalWrite(RF_RST_PIN, HIGH );
	bcm2835_delay(100);
	#endif

	#ifdef RF_LED_PIN
	printf( ", LED=GPIO%d", RF_LED_PIN );
	digitalWrite(RF_LED_PIN, LOW );
	#endif

	if (!rf95.init()) {
	fprintf( stderr, "\nRF95 module init failed, Please verify wiring/module\n" );
	} else {
		printf( "\nRF95 module seen OK!\r\n");
	
		#ifdef RF_IRQ_PIN
		// Since we may check IRQ line with bcm_2835 Rising edge detection
		// In case radio already have a packet, IRQ is high and will never
		// go to low so never fire again
		// Except if we clear IRQ flags and discard one if any by checking
		rf95.available();
	
		// Now we can enable Rising edge detection
		bcm2835_gpio_ren(RF_IRQ_PIN);
		#endif
	
		// Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
	
		// The default transmitter power is 13dBm, using PA_BOOST.
		// If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
		// you can set transmitter powers from 5 to 23 dBm:
		//rf95.setTxPower(23, false);
		// If you are using Modtronix inAir4 or inAir9,or any other module which uses the
		// transmitter RFO pins and not the PA_BOOST pins
		// then you can configure the power transmitter power for -1 to 14 dBm and with useRFO true
		// Failure to do that will result in extremely low transmit powers.
		//rf95.setTxPower(14, true);
	
		rf95.setTxPower(14, false);
	
		// You can optionally require this module to wait until Channel Activity
		// Detection shows no activity on the channel before transmitting by setting
		// the CAD timeout to non-zero:
		//rf95.setCADTimeout(10000);
	
		// Adjust Frequency
		rf95.setFrequency( RF_FREQUENCY );
	
		// This is our Node ID
		rf95.setThisAddress(RF_NODE_ID);
		rf95.setHeaderFrom(RF_NODE_ID);
	
		// Where we're sending packet
		rf95.setHeaderTo(RF_GATEWAY_ID);
	
		printf("RF95 node #%d init OK @ %3.2fMHz\n", RF_NODE_ID, RF_FREQUENCY );
	
		last_millis = millis();
	
		//create string with number of packet
		stringstream  packet_nr_rec_preform;
		string  packet_nr_rec;
	
		//remove lines
		string buf_to_temp_data;
	
	
		//DEMO TEST!!! FILL RANDOM SENSOR VALUES INTO CSV FILE
		ofstream ip_temp(FILENAME);
		int x;
		char csv_writer[55];
	
		for(x=0;x<1000;x++){
		sprintf(csv_writer,"5-10-2017;13:14:00;500.56;1025.76;0.0;1.03;0.5;0.0;19.7;95.3;");
		ip_temp<<csv_writer<<endl;
		}
		ip_temp.close();
	
		uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
		uint8_t len = sizeof(buf);
		uint8_t data[6];	
	
		//Begin the main body of code
		while (!force_exit) {
			
			// Send every 5 seconds
			if ( millis() - last_millis > SENDSPEED ) {
				last_millis = millis();
				
				//READ CSV
				//read csv file and convert the string to an uint8_t array
				//the uint8_t array is send to the server
				string csv_data;
			
				//OPEN CSV FILE
				ifstream ip(FILENAME);
				ofstream ip_temp(FILENAME_TEMP);
				
				//WHILE CSV HAS NOT REACHED END OF FILE
				if(ip.good()){
					getline(ip,csv_data,'\n');
			
					//GET PACKET NUMBER
					sprintf(packet_nr_send,"%03d::",packet_nr);
					printf("\n:::Sending:::\n");
					printf("\tPacket Nr. %c%c%c\n",packet_nr_send[0],packet_nr_send[1],packet_nr_send[2]);
			                  
					//GET MESSAGE ID
					sprintf(message_id, "%01d::", 0);
			
					//Check if csv line is not empty and if send data is not saved
					if(!csv_data.empty()){
						int x;
						uint8_t data[csv_data.length()+8];
			
						//fill first part of buffer with message id
						for (x=0;x<3;x++){
							data[x]=message_id[x];
						}
			
						//Fill first part of buffer with the packet number
						for (x=0;x<5;x++){
							data[x+3]=packet_nr_send[x];
						}
			
						//Fill the rest of the buffer with csv data
						for (x=0;x<csv_data.length();x++){
							data[x+8]=csv_data[x];
						}
				    		uint8_t send_length = sizeof(data);
			
						//SENDING TO SERVER
						rf95.setModeTx();
						sleep(1);
						printf("\tSending %02d bytes to node #%d => ", send_length, RF_GATEWAY_ID );
						printbuffer(data, send_length);
						printf("\n" );
						rf95.send(data, send_length);
						rf95.waitPacketSent();
					}
					else{
						printf("Empty line in CSV File\n");
					}
				}
				else{
					printf("Reached end of file\n");
				}
			}
			
			//RECEIVING
			printf("\n:::Receiving:::\n");
			rf95.setModeRx();
			sleep(1);
			printf("\tsearching for command.....");	
			if (rf95.waitAvailableTimeout(RECEIVESPEED)) {
				for(int i=0;i<sizeof(buf);i++){
					buf[i] = 0;
				}
				uint8_t len = sizeof(buf);
				rf95.recv(buf, &len);
				printf("\t\treceived command: %c with message: %s\n", buf[0], buf);
				
				if(buf[0] == '2'){
					packet_nr_send[0] = buf[3];
					packet_nr_send[1] = buf[4];
					packet_nr_send[2] = buf[5];
					sprintf(message_id, "%01d::", 1);
					
					for (int x=0;x<3;x++){
						data[x+3]=packet_nr_send[x];
						data[x]=message_id[x];
					}
					uint8_t send_length = sizeof(data);
					printf("\tSending %02d bytes to node #%d => ", send_length, RF_GATEWAY_ID );
					printbuffer(data, send_length);
					printf("\n" );
					rf95.send(data, send_length);
				}
			
				if (buf[0]=='3'){
					//READ CSV
					//read csv file and convert the string to an uint8_t array
					//the uint8_t array is send to the server
					string csv_data;
				
					//OPEN CSV FILE
					ifstream ip(FILENAME);
					ofstream ip_temp(FILENAME_TEMP);
					if (!ip.is_open()){
						printf("ERROR, Not possible to open file\n\n");
					}
					ip.clear();
					ip.seekg(0, ios::beg);
				  //Check if send number and received number are equal
					if (buf[3]==packet_nr_send[0] && buf[4]==packet_nr_send[1] && buf[5]==packet_nr_send[2]){
						if (buf[6]=='n'){
								printf("\tNumber compare completed but data is NOT saved!\n");
						}
						else if (buf[6]=='s'){
							printf("\tNumber Compare completed and data saved!\n");
							printf("\tData will be deleted from CSV file\n");
							//saved=true;

							while(ip.good()){
				  			getline(ip,buf_to_temp_data,'\n');
					    	ip_temp<<buf_to_temp_data<<endl;
							}

							ip.close();
							ip_temp.close();

							if (remove(FILENAME) != 0){
								printf("\tremove FAILED!\n");
								perror("\terror\n");
							}
							rename(FILENAME_TEMP,FILENAME);

							//Create new packet number
							packet_nr++;
							if (packet_nr > 999){ packet_nr = 0;}
						}
					}
					else{
						printf("\tNumber compare completed but packet numbers dont match\n");
					}
				}  
			}
			else{
				printf("\tno command received\n");
			}
			bcm2835_delay(100);
		}
	
	#ifdef RF_LED_PIN
	  digitalWrite(RF_LED_PIN, LOW );
	#endif
	  printf( "\n%s Ending\n", __BASEFILE__ );
	  bcm2835_close();
	  return 0;
	}
}

