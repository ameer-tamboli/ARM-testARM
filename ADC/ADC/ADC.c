#include<lpc17XX.h>
#include<stdio.h>
char buffer [50];
void UART_INIT()
{
	LPC_PINCON->PINSEL0 =(1<<1)|(1<<3); // CONFIGURING PINS OF CONTROLLER TO ACT AS TXD AND RXD OF UART3 
	LPC_SC ->PCONP = (1<<25); // ENABLING THE UART3
	LPC_SC ->PCLKSEL1 = (0<<19)|(0<<18); // THIS WILL GIVE THE PCLK = 100/4 = 25MHZ
	LPC_UART3 ->LCR = (1<<0)|(1<<1)|(1<<7); // ENABLING THE DLAB BIT SO THAT WE CAN ACCES DLL AND DLM TO SET THE VALUE FOR REQUIED BAID RATE& 1STOP BIT&8 BIT CHAR LENGTH&NO PARITY
	LPC_UART3 ->DLL = 0XA2; 		// THIS SETTING WILL SET THE BAUD RATE 9600
	LPC_UART3 ->DLM = 0X00;
	LPC_UART3 ->LCR = (1<<0)|(1<<1)|(0<<7); // DISABLING THE DLAB BIT SO THAT UART3 CAN TRANSMIT AND RECEIVE
	LPC_UART3->TER = (1<<7); // ENABLE THE TRANSMISSION
}



void ADC_INIT()
{
	LPC_SC->PCONP |= (1<<12); //ACTIVATING THE ADC
	LPC_SC->PCLKSEL0 |=(0<<25)|(0<<24);//PCLK FO ADC
	LPC_PINCON->PINSEL1|=(1<<18); //ENABLING THE PIN FUNCTION AS ADC CHANNEL2
	LPC_ADC->ADCR |=(1<<1)|(1<<8)|(1<<16)|(1<<21);//SELECT ADC CHANNEL 2,CLOCK FREQUENCY =25/2=12.5,BRUST MODE,KEEPING ADC IN OPERATIONAL MODE
}


void ADC_DATA()
{
	while(!(LPC_ADC->ADSTAT&0X10));
			int data = LPC_ADC->ADDR2&(0X0000FFF0);
					data = (data>>4);
		sprintf(buffer, "%d" , data);
}


void UART_TRANSMIT_STRING(char DATA [50])
{
	for(int i=0;DATA[i]!='\0';i++)
	{
		while(!(LPC_UART3->LSR&(0X20)));
			LPC_UART3->THR =DATA[i];
	}
}

int main()
	
{
	UART_INIT();
	ADC_INIT();
	ADC_DATA();
	UART_TRANSMIT_STRING(buffer);
}









