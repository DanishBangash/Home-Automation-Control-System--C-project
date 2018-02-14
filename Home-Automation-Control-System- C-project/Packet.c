#include "Packet.h"
#include "UART.h"       // Define functions in serialio.c
#include <stdio.h>
#include <stdlib.h>
#include"Lcd.h"
/////////////////////////////////////////////////////////////////////////
//                       Local variables                               //
/////////////////////////////////////////////////////////////////////////	
		
	unsigned char SOURCE = 12;
	unsigned char DESTINATION = 34;
	char source;
	char destination;
	char command;
	char dataLength;
	char checksum;
	char dataBuffer[50];
/////////////////////////////////////////////////////////////////////////
//                       Public functions                              //
/////////////////////////////////////////////////////////////////////////
void sendpacket(unsigned char command, char data[]){

	//Construct packet and encode to ASCII
	char buffer[50];
	sprintf(buffer, "%02d%02d%02d0000",
		SOURCE,
		DESTINATION,
		command);
		// 	Construct packet and encode to ASCII.
	char packet[50];
	sprintf(packet,"%s%02d", buffer);
	//send packet.
	PutString(packet);
	LCDPutString("packet sent");
}
// Receive packet from the hacs.
// returns 1 if data checksum is correct
// Returns 0 if data checksum is incorrect
void receivePacket(){
	char headerBuffer[3] = {0, 0, 0};
	char sizeBuffer[5];
	char packetBuffer[50];
	unsigned char i = 0;
	unsigned char k = 0;
	// receive source = 2 bytes.
	while(i<=1){
		headerBuffer[i] = uart_recieve();
		packetBuffer[k] = headerBuffer[i];
		k++;
		i++;
	}
	source = atoi(headerBuffer);


	//receive destination = 2 bytes.
	i = 0;
	while(i<=1){
		headerBuffer[i] = uart_recieve();
		packetBuffer[k] = headerBuffer[i];
		k++;
		i++;
	}
	destination = atoi(headerBuffer);
	

	//receive command = 2 bytes.
	i = 0;
	while(i<=1){
		headerBuffer[i] = uart_recieve();
		packetBuffer[k] = headerBuffer[i];
		k++;
		i++;
	}
	command = atoi(headerBuffer);


	// receive packet size = 4 bytes.
	i = 0;
	while(i<=3){
		sizeBuffer[i] = uart_recieve();
		packetBuffer[k] = sizeBuffer[i];
		k++;
		i++;
	}
	sizeBuffer[4] = 0;
	dataLength = atoi(sizeBuffer);


	// receive the data.
	i = 0;
	while(i<dataLength){
		dataBuffer[i] = uart_recieve();
		packetBuffer[k] = dataBuffer[i];
		k++;
		i++;
	}
	dataBuffer[i] = 0;
	packetBuffer[k] = 0;
	LCDPutString("packet recieved");
}

