// rf95_server.cpp
//
// Example program showing how to use RH_RF95 on Raspberry Pi
// Uses the bcm2835 library to access the GPIO pins to drive the RFM95 module
// Requires bcm2835 library to be already installed
// http://www.airspayce.com/mikem/bcm2835/
// Use the Makefile in this directory:
// cd example/raspi/rf95
// make
// sudo ./rf95_server
//
// Contributed by Charles-Henri Hallard based on sample RH_NRF24 by Mike Poublon
//------
#include <string.h>    //strlen
#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr
#include <iostream>

#include <bcm2835.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include <RH_RF69.h>
#include <RH_RF95.h>

//TCP/IP defines:
#define BASE_STATION_IP_ADDRESS "192.168.1.9" //LoRa Gateway: "192.168.2.80" //"192.168.0.22" //"127.0.0.1" //"192.168.0.102" 
#define PORT 8080
#define MESSAGE_LENGTH 1000
#define SERVER_REPLY_LENGTH 2000
#define SOCKET_ERROR -1

using namespace std;

// define hardware used change to fit your need
// Uncomment the board you have, if not listed 
// uncommment custom board and set wiring tin custom section

// Dragino Raspberry PI hat
// see https://github.com/dragino/Lora
#define BOARD_DRAGINO_PIHAT

// Now we include RasPi_Boards.h so this will expose defined 
// constants with CS/IRQ/RESET/on board LED pins definition
#include "RadioHead/examples/raspi/RasPiBoards.h"

// Our RFM95 Configuration 
#define RF_FREQUENCY  868.00
#define RF_NODE_ID    1	  //lora gateway 	
#define RF_GATEWAY_ID 10  //agv lora 

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
	int sock;
	struct sockaddr_in server;
    char /*message[MESSAGE_LENGTH] ,*/ server_reply[SERVER_REPLY_LENGTH];    
    //Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	
	if (sock == SOCKET_ERROR){
		cout<<"Could not create socket at: "<<BASE_STATION_IP_ADDRESS<<":"<<PORT<<endl;
	}
	
	cout<<"Socket created"<<endl;    
	server.sin_addr.s_addr = inet_addr(BASE_STATION_IP_ADDRESS);
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	    //Connect to remote server
	while (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0){//Try to connect to server
		cout<<"Connect failed at: "<<BASE_STATION_IP_ADDRESS<<":"<<PORT<<endl;
		sleep(1);
	}    
	puts("Connected\n");    

	unsigned long led_blink = 0;

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
	  // Now we can enable Rising edge detection
	bcm2835_gpio_ren(RF_IRQ_PIN);
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
	} 
	else {
	    // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

	    // The default transmitter power is 13dBm, using PA_BOOST.
	    // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
	    // you can set transmitter powers from 5 to 23 dBm:
	    //  driver.setTxPower(23, false);
	    // If you are using Modtronix inAir4 or inAir9,or any other module which uses the
	    // transmitter RFO pins and not the PA_BOOST pins
	    // then you can configure the power transmitter power for -1 to 14 dBm and with useRFO true. 
	    // Failure to do that will result in extremely low transmit powers.
	    // rf95.setTxPower(14, true);


	    // RF95 Modules don't have RFO pin connected, so just use PA_BOOST
	    // check your country max power useable, in EU it's +14dB
		rf95.setTxPower(14, false);

	    // You can optionally require this module to wait until Channel Activity
	    // Detection shows no activity on the channel before transmitting by setting
	    // the CAD timeout to non-zero:
	    //rf95.setCADTimeout(10000);

	    // Adjust Frequency
		rf95.setFrequency(RF_FREQUENCY);

	    // If we need to send something
		rf95.setThisAddress(RF_NODE_ID);
		rf95.setHeaderFrom(RF_NODE_ID);

	    //GATEWAY
		rf95.setHeaderTo(RF_GATEWAY_ID);

	    // Be sure to grab all node packet 
	    // we're sniffing to display, it's a demo
		rf95.setPromiscuous(false);

	    // We're ready to listen for incoming message
		rf95.setModeRx();

		printf( " OK NodeID=%d @ %3.2fMHz\n", RF_NODE_ID, RF_FREQUENCY );
		printf( "Listening packet...\n" );		

	    //Begin the main body of code
		while (!force_exit) {

			#ifdef RF_IRQ_PIN
	     	 // We have a IRQ pin ,pool it instead reading
	     	 // Modules IRQ registers from SPI in each loop

	  	    // Rising edge fired ?
			if (bcm2835_gpio_eds(RF_IRQ_PIN)) {
	 	       // Now clear the eds flag by setting it to 1
				bcm2835_gpio_set_eds(RF_IRQ_PIN);
	        //printf("Packet Received, Rising event detect for pin GPIO%d\n", RF_IRQ_PIN);
			#endif

				if (rf95.available()) { 
				#ifdef RF_LED_PIN
					led_blink = millis();
					digitalWrite(RF_LED_PIN, HIGH);
					#endif
	         	// Should be a message for us now
					uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
					uint8_t len  = sizeof(buf);
					uint8_t from = rf95.headerFrom();
					uint8_t to   = rf95.headerTo();
					uint8_t id   = rf95.headerId();
					uint8_t flags= rf95.headerFlags();;
					int8_t rssi  = rf95.lastRssi();

					if (rf95.recv(buf, &len)) {//If data is revied over LoRa
						printf("LoRa:: ");
						if(buf[0] == '0') printf("AGV Data: ");
						if(buf[0] == '1') printf("AGV Reply: ");
						//printf("Packet[%02d] #%d => #%d %ddB: ", len, from, to, rssi);
						printbuffer(buf, len);
						if(from == RF_GATEWAY_ID){
							bool message_valid = true;
							char message[len]={0};
							for(int x=0; x<len; x++){
								message[x] = buf[x];
								//check if the chars are valid:
								if(message[x] <48 || message[x]>59){ //0123456789:;
									if(!(message[x]==46 || message[x]==43 || message[x]==32 || message[x]==45)){ //. space -
										//message error
										cout<<"\nX: "<<x<<" Ascii value: ";
										printf("%d \n",message[x]);
										message_valid = false;
										break;
									}
								}
							}	
							if(message_valid){	
								//cout<<"\ntcp ip message: "<<message<<endl;
								//Send data to base station
								if( send(sock , message , strlen(message) , 0) < 0){
									cout<<"Send failed"<<endl;
									return 1;
								}
								for(int i =0; i<sizeof(buf);i++){
									buf[i]=0;
								}

							}else{
								cout<<"Message NOT valid!!"<<endl;
							}
						}else{
							cout<<"Drop received data: Data is not from the AGV."<<endl; 
						}
					} else {
						Serial.print("receive failed");
					}
					printf("\n");
				}

			#ifdef RF_IRQ_PIN
			}
			#endif
			int recieved = recv(sock , server_reply , SERVER_REPLY_LENGTH , MSG_DONTWAIT);//Non blocking get data from tcp
			if(recieved > 0){
				//Receive a reply from the base station server
				printf("TCP:: ");
				if(server_reply[0] == '2')cout<<"Basestation Data: "<<server_reply<<endl;
				if(server_reply[0] == '3')cout<<"Basestation Reply: "<<server_reply<<endl;
				uint8_t loraReply[strlen(server_reply)];
				for(int x=0; x<strlen(server_reply);x++){
					loraReply[x] = server_reply[x];
				}

				rf95.send(loraReply,sizeof(loraReply));
				rf95.waitPacketSent();
				//printf("Data has been send to %d \n",RF_GATEWAY_ID);

				rf95.setModeRx();
				for(int i =0; i<sizeof(server_reply);i++){
					server_reply[i]=0;
				}
			}
			else {
				if(recieved == 0){//If connection closed
					close(sock);//Create new connection
					sock = socket(AF_INET , SOCK_STREAM , 0);
					while (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0 && !force_exit){
						cout<<"Reconnecting at: "<<BASE_STATION_IP_ADDRESS<<":"<<PORT<<endl;
						sleep(1);
					} 
				}
			}
			#ifdef RF_LED_PIN
		      // Led blink timer expiration ?
			if (led_blink && millis()-led_blink>200) {
				led_blink = 0;
				digitalWrite(RF_LED_PIN, LOW);
			}
			#endif
		      // Let OS doing other tasks
		      // For timed critical appliation you can reduce or delete
		      // this delay, but this will charge CPU usage, take care and monitor
			bcm2835_delay(5);
		}
	}

	#ifdef RF_LED_PIN
	digitalWrite(RF_LED_PIN, LOW );
	#endif
	close(sock);
	printf( "\n%s Ending\n", __BASEFILE__ );
	bcm2835_close();
	return 0;
}

