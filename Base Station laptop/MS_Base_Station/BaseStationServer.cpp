/*
*   TCP/IP (socket) Base Station application 
*/
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#define FILENAME "BaseStationMeasurementData.csv"
#define SAVED "saved"
#define NOTSAVED "not saved" 

int writeToFile(char filename[], char text[]){
   //printf("text: %s \n", text);
   FILE *fp;
   fp = fopen(filename, "a");
   if(!fp){
     fclose(fp);
     return 0;
   }else{
     fprintf(fp, "%s\n",text);
     //fprintf(fp, "\n");
     fclose(fp);
     return 1;
   }
}

int getNum(char array[]){
	int value = 0;	
	int multiplier[3] = {100,10,1};
	for(int i = 0; i < 3;i++){
		value += (array[i + 3] - '0') * multiplier[i];		
	}
	return (value);
}


int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size=1,lastRecievedDataPacketNum = -1,lastRecievedReplyPacketNum = -1,packet_nr =0;
    bool commandPending = 0;
    char packet_nr_send[3];
    char command[200] = {'2',':',':'};
    struct sockaddr_in server , client;
        
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8080 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
	close(socket_desc);
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0){
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
     
    //Receive a message from client
    while(read_size != 0 ){//While connected
	char client_message[2000]={0};
	read_size = recv(client_sock , client_message , 2000 , MSG_DONTWAIT);
	if(read_size > 0){
		for(int i=0; i<(strlen(client_message)); i++){
			if(client_message[i]<32){
				//printf("False ID: %d\n",(int)client_message[i]); 
				client_message[i] =0;
			}
		}
		if(client_message[0] == '0'){//Data message
			printf("Received AGV Data: %s\n", client_message);	
			//Send the message back to client
			int dataOffset = 8;
			char msg[2000-8]={0};
			for(int i=dataOffset; i<(strlen(client_message)); i++){
				if(client_message[i]==':' &&  client_message[i-1]=='1' && i>0){
					msg[i-dataOffset -1] = 0;
					break;
				}
				msg[i-dataOffset]=client_message[i];
			}
			//printf("msg: %s \n", msg);
			char reply_message[20]={'3',':',':'};
			reply_message[3]=client_message[3];
			reply_message[4]=client_message[4];
			reply_message[5]=client_message[5];
			int packetnum = getNum(reply_message);
			//printf("Packet: %d\n",packetnum); 
			if(lastRecievedDataPacketNum != packetnum){
			    	if(writeToFile(FILENAME,msg) == 1){
					printf("Data saved in: %s\n", FILENAME); 
				  	for(int i=0; i<sizeof(SAVED); i++){
				    		reply_message[i+6]=SAVED[i];
				  	}
					lastRecievedDataPacketNum = packetnum;       
				}
				else{
					printf("ERROR: data NOT saved!\n");
				  	for(int i=0; i<sizeof(NOTSAVED); i++){
				    		reply_message[i+6]=NOTSAVED[i];
				  	}          
			    	}
			}
			else {
				for(int i=0; i<sizeof(SAVED); i++){
				    	reply_message[i+6]=SAVED[i];
				}
			}
		    	printf("Sending Reply: %s \n", reply_message);
		    	write(client_sock , reply_message , strlen(reply_message));
		}
		else if(client_message[0] == '1'){//Reply message
			printf("Received AGV Reply: %s\n", client_message);	
			lastRecievedReplyPacketNum = getNum(client_message);
			//printf("GOT REPLY: %d \n",lastRecievedReplyPacketNum);
			
		}
	}
	sleep(1);
	if(!commandPending){//If command needs to be send
		sprintf(packet_nr_send,"%03d::",packet_nr);
		for(int i =0; i<sizeof(command);i++){
			command[i]=0;
		}
		command[0] = '2';
		command[1] = ':';
		command[2] = ':';
		command[3] = packet_nr_send[0];
 		command[4] = packet_nr_send[1];
		command[5] = packet_nr_send[2];
		command[6] = ':';
		command[7] = ':';
		command[8] = '6';
		for(int i = 0;i<20;i++){
			command[i+9] = '0' + i;
		}
		commandPending = 1;
	}

	if(commandPending){
		if(packet_nr == lastRecievedReplyPacketNum){
			commandPending = 0;
			packet_nr++;
		}
		else{
			write(client_sock , command , strlen(command));
			printf("Sending Data: %s \n",command);
		}	
	}
	sleep(1);
	//printf("Loop");
    }
    puts("Client disconnected");
    fflush(stdout);
    return 0;
}
