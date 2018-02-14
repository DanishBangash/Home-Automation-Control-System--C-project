#include "RFIDstate.h"

	 int main()
	 {
	  	init();
  		lcd_init();
	 	init_uart( 0x40);
		SPI_MasterInit();
		key_init();
		  while (1)
		  {		
			 {	
			//	_delay_ms(10);
				EnterPassword();
			/*	_delay_ms(500);
				lcdClear();	
				_delay_ms(500);
				*/
					}	
					}
		  }
	

