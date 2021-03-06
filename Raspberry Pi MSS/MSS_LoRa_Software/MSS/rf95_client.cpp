
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

#define BOARD_DRAGINO_PIHAT
#include "RadioHead/examples/raspi/RasPiBoards.h"

using namespace std;

// Our RFM95 Configuration
#define RF_FREQUENCY  868.00
#define RF_GATEWAY_ID 1
#define RF_NODE_ID    10

#define SENDSPEED 500 
#define RECEIVESPEED 5
#define BUFFERSIZE 20

#define SEPARATION_SYMBOL ";"
#define SEP SEPARATION_SYMBOL
#define RECEIVE true
#define SEND false
#define INSTANT 0
#define QUEUE 1
#define CINSTANT '0'
#define CQUEUE '1'

//Define csv filename with measurement data:
#define FILENAME "/media/mss/MSS_USB7/measurements/measurement.csv"
#define FILENAME_TEMP "/media/mss/MSS_USB7/measurements/measurement_temp.csv"

//Define csv filename with commands:
#define FILENAME_INSTANT_COMMAND_CSV "/media/mss/MSS_USB7/commands/instant_commands.csv"
#define FILENAME_QUEUE_COMMAND_CSV "/media/mss/MSS_USB7/commands/Queue_commands.csv"

// Create an instance of a driver
RH_RF95 rf95(RF_CS_PIN, RF_IRQ_PIN);

//Flag for Ctrl-C
volatile sig_atomic_t force_exit = false;

vector <string> buffer;
int errorCnt = 0;
bool received = false;
bool send_receive_state = true;


void sig_handler(int sig)
{
  printf("\n%s Break received, exiting!\n", __BASEFILE__);
  force_exit=true;
}


int getNum(uint8_t array[])
{
	int value=0;
	int multiplier[3] = {100,10,1};
	for(int o=0;o<3;o++){
		value+=(array[o+3] - '0') * multiplier[o];
	}
	return(value);
}


void save_to_csv(uint8_t incoming_data[], int size_of_array, int message_type)
{	
	printf("\tsize data: %d\tdata: %s\n", size_of_array, incoming_data);
	if (size_of_array > 11){
		uint8_t temp_data[size_of_array-11];
		for(int temp=0;temp<size_of_array-11;temp++){
			temp_data[temp] = incoming_data[temp+11];
		}
		std::ostringstream oss;
		string tempString;
		oss<<temp_data<<endl;
		tempString = oss.str();
		cout << "\tsaving: " << tempString << endl;
		ofstream myfile;
		if (message_type == INSTANT) myfile.open(FILENAME_INSTANT_COMMAND_CSV, ios::out |ios::app);
		else if(message_type == QUEUE) myfile.open(FILENAME_QUEUE_COMMAND_CSV, ios::out |ios::app);
		
		cout << "\tmessage type: " << message_type << endl;
		if (myfile.is_open())
		{ 
			if(errorCnt > 0){
				printf("\tSaving data from buffer to csv\n");
				for(int i=0;i<errorCnt;i++){
					myfile << buffer[i];		
				}
				buffer.clear();
				errorCnt = 0;
			}
			myfile << tempString;
			printf("\tSaving data to csv\n");	
			myfile.close();
		}
		else{
			printf("\tSave_Measurement_to_file: Unable to open file!\n");
			//cout << "Unable to open file"
			if(buffer.size()<BUFFERSIZE){
			    //buffer[errorCnt] = tempString;
			    buffer.push_back(tempString);
			    printf("\tMeasurement added to buffer: %s\n", buffer[errorCnt].c_str());
			    errorCnt++;
			}else{
				buffer.clear();
				errorCnt=0;
			}
	  }
	}else{
		printf("\tdata is not long enough to save in csv file\n");
	}
}

//Main Function
int main (int argc, const char* argv[] )
{
	static unsigned long last_millis;
	static unsigned long led_blink = 0;
	uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
	
	//create boolean saved to check if packet is saved
	int csv_send_packet_nr = 0;
	int command_received_packet_nr = -1;
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
		
		rf95.setModeRx();
		sleep(1);
		send_receive_state = RECEIVE;
			
		last_millis = millis();
	
		//create string with number of packet
		stringstream  packet_nr_rec_preform;
		string  packet_nr_rec;
	
		//remove lines
		string buf_to_temp_data;
		
		uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
		uint8_t len = sizeof(buf);
		uint8_t data[6];	
	
		//Begin the main body of code
		while (!force_exit) {
			
			// Send every amount of seconds
			if ( millis() - last_millis > SENDSPEED ) {
				
				//SENDING TO LoRa server
				last_millis = millis();
				received = false;
				if(send_receive_state != SEND){
			        send_receive_state = SEND;  
				}
				
				//read csv file and convert the string to an uint8_t array
				//the uint8_t array is send to the server
				string csv_data;
			
				//OPEN CSV FILE
				ifstream ip(FILENAME);
				
				//WHILE CSV HAS NOT REACHED END OF FILE
				if(ip.good()){
					getline(ip,csv_data,'\n');
			
					//GET PACKET NUMBER
					sprintf(packet_nr_send,"%03d::",csv_send_packet_nr);

					//GET MESSAGE ID
					sprintf(message_id, "%01d::", 0);
			
					//Check if csv line is not empty and if send data is not saved
					if(!csv_data.empty()){
						printf("\n:::Sending:::\n");
						int x;
						uint8_t data[csv_data.length()+8];
			
						//fill first part of buffer with message id
						for (x=0;x<3;x++){
							data[x]=message_id[x];
						}
			
						//Fill second part of buffer with the packet number
						for (x=0;x<5;x++){
							data[x+3]=packet_nr_send[x];
						}
			
						//Fill the rest of the buffer with csv data
						for (x=0;x<csv_data.length();x++){
							data[x+8]=csv_data[x];
						}
			    		uint8_t send_length = sizeof(data);
			
						printf("\tSending %02d bytes to node #%d => ", send_length, RF_GATEWAY_ID );
						printbuffer(data, send_length);
						printf("\n" );
						rf95.send(data, send_length);
						rf95.waitPacketSent();
						rf95.setModeRx();
					}
				}
			}
			//RECEIVING
			if(send_receive_state != RECEIVE) send_receive_state = RECEIVE;

			if (rf95.available()) { 
				printf("\n:::Receiving:::\n");
				received = true;
				
				for(int i=0;i<sizeof(buf);i++){
					buf[i] = 0;
				}
				uint8_t len = sizeof(buf);
				rf95.recv(buf, &len);
				printf("\treceived command: %c with message: %s\n", buf[0], buf);
				if(len > 0){
					int result = getNum(buf);
					switch(buf[0]){
						case('2'):
						{
							if (result != command_received_packet_nr) {
								if(buf[8] == CINSTANT){
									printf("\tsaving instant command to csv\n");
									save_to_csv(buf, sizeof(buf), INSTANT);
								}
								else if(buf[8] == CQUEUE){
									printf("\tsaving queue command to csv\n");
									save_to_csv(buf, sizeof(buf), QUEUE);
								}
							}
						    command_received_packet_nr = result;
						    
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
							rf95.waitPacketSent();
							rf95.setModeRx();
						}
						break;
				
						case('3'):
						{
							//OPEN CSV FILE
							ifstream ip(FILENAME);
							ofstream ip_temp(FILENAME_TEMP);
							if (!ip.is_open()){
								printf("ERROR, Not possible to open file\n\n");
							}
							
							ip.clear();
							ip.seekg(0, ios::beg);
							//Check if send number and received number are equal
							if (result == csv_send_packet_nr){
								if (buf[6]=='n'){
										printf("\tNumber compare completed but data is NOT saved!\n");
								}
								else if (buf[6]=='s'){
									printf("\tNumber Compare completed and data saved!\n");
									printf("\tData will be deleted from CSV file\n");
	
									getline(ip,buf_to_temp_data,'\n');
									while(ip.good()){
							        	getline(ip,buf_to_temp_data,'\n');
										if(!buf_to_temp_data.empty()) ip_temp<<buf_to_temp_data<<endl;
									}
		
									ip.close();
									ip_temp.close();
		
									if (remove(FILENAME) != 0){
										printf("\tremove FAILED!\n");
										perror("\terror\n");
									}
									else{
										//Create new packet number
										csv_send_packet_nr++;
										if (csv_send_packet_nr > 999) csv_send_packet_nr = 0;
									}
									rename(FILENAME_TEMP,FILENAME);
								}
							}
							else printf("\tNumber compare completed but packet numbers dont match\n");
						}
						break;
						
						default: printf("command is unknown");
					}
				}
			}
			bcm2835_delay(RECEIVESPEED);
		}
	
	#ifdef RF_LED_PIN
	  digitalWrite(RF_LED_PIN, LOW );
	#endif
	  printf( "\n%s Ending\n", __BASEFILE__ );
	  bcm2835_close();
	  return 0;
	}
}

