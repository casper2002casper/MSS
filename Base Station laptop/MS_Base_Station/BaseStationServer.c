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

int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size=1;
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
    while(read_size> 0 ){
	char client_message[2000]={0};
	read_size = recv(client_sock , client_message , 2000 , 0);
        //Send the message back to client
	printf("Received data: %s\n", client_message);
	//puts(client_message);
	char msg[2000-5]={0};
	for(int i=5; i<(strlen(client_message)); i++){
		msg[i-5]=client_message[i];
	}
	//printf("msg: %s \n", msg);
	char reply_message[20]={0};
        if(writeToFile(FILENAME,msg) == 1){
	  printf("Data saved in: %s\n", FILENAME); 
	  reply_message[0]=client_message[0];
	  reply_message[1]=client_message[1];
	  reply_message[2]=client_message[2];
	  for(int i=0; i<sizeof(SAVED); i++){
            reply_message[i+3]=SAVED[i];
	  }       
	}else{
	  printf("ERROR: data NOT saved!\n");
	  reply_message[0]=client_message[0];
	  reply_message[1]=client_message[1];
	  reply_message[2]=client_message[2];
	  for(int i=0; i<sizeof(NOTSAVED); i++){
            reply_message[i+3]=NOTSAVED[i];
	  }          
        }
        printf("reply msg: %s \n", reply_message);
        write(client_sock , reply_message , strlen(reply_message));

    }
     
    if(read_size == 0){
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1){
        perror("recv failed");
    }
     
    return 0;
}
