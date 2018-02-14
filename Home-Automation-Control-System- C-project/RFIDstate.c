#include "RFIDstate.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#define max 14
	char data=0;
	char key;
	volatile char spi_data_ready =0;
volatile unsigned char spi_flag=0;
	char buffer[max];
	char Hexbuffer[2];
	volatile int i=max-1; 
	volatile int j=0;
	volatile int ii=0;
void RFID_state(){
		  if (spi_data_ready==1){
					spi_data_ready=0;
			    	uart_transmit(buffer[i]); // to transmit data into terminal
					 LCDPutString("Welcome!!!!!");
					_delay_ms(2000);
					lcdClear();
					LCDPutString("Your ID :");
					_delay_ms(100);	
					LCDPutString(buffer);
					}
				 }
//void intterupts(){

ISR(INT0_vect)
	{
		LCDPutString("Enter PIN :");
	 SPI_MasterTransmit(0x55);  //getting the uid from rfid tag
	}
	 ISR(INT1_vect)
	 {
	  TIMSK |=(1<<TOV0);
	 
	  if (spi_flag==1)
	  {
	  
	   TIMSK &=~(1<<TOV0);
	   spi_flag=0;
	  
	  }
	   spi_flag=1;
	 }
	 ISR(TIMER0_OVF_vect)
	 {
		
	  SPI_MasterTransmit(0xF5);
	 data=SPDR;
	 if((j<max)&&(data!=0x86)){//
	 sprintf(Hexbuffer, "%02X", data);
		buffer[i]=Hexbuffer[1];
		i--;
	
		buffer[i]=Hexbuffer[0];
		ii=0;
		i--;
		 PORTB &=0xFE;
		}
	 
	 if (j==max-7) {
	 spi_data_ready=1;
	  j=0;
	 i=max-1;
	 }
	 else j++;
}
	
	ISR(USART_RXC_vect)
{
		lcd_data_write(uart_recieve());
		  
}


