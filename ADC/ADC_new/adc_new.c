#include<LPC17xx.h>

#include<stdio.h>
void adc_init();
void UART_init();
void UART_TRANSMIT_STRING();
void UART_TRANSMIT_STRING_HC();

void adc_init(){
	
	
	LPC_PINCON->PINSEL1|=(1<<18)|(0<<19);
	LPC_SC->PCLKSEL0=(0<<25)|(0<<24);   //25MHz
	LPC_ADC->ADCR=(1<<8)|(1<<21)|(1<<2)|(1<<16);
	
	}

void UART_init()
{
		LPC_PINCON->PINSEL0|=(1<<1)|(1<<3);
	

	LPC_SC->PCLKSEL1=(0<<18)|(0<<19);
	
	LPC_UART3->LCR=(1<<0)|(1<<1)|(1<<7);
	LPC_UART3->DLL=0xA2;
	LPC_UART3->DLM=0x00;
	LPC_UART3->LCR=(1<<0)|(1<<1)|(0<<7);
	
	LPC_UART3->TER=(1<<7);
}

char buffer[50];
int main(){
						LPC_SC->PCONP|=(1<<12)|(1<<25);
						LPC_GPIO2->FIODIR1=(1<<1);
						adc_init();
						UART_init();
					//UART_INIT();
					int result;
						UART_TRANSMIT_STRING_HC();
	
						while(!(LPC_ADC->ADSTAT&(0x04)));
	
						for(int j=0;j<1000;j++)
						{
							for(int k=0;k<1000;k++);
						}
						LPC_GPIO2->FIOSET1=(1<<1);
						result=(LPC_ADC->ADDR2)&0xFFF0;
           result=(result>>4);
	
						
					int i=0;
						sprintf(buffer,"%d",result);
						//while(buffer[i]!='\0')
					//	{
					//	while(!(LPC_UART3->LSR&(0x20)));
					//	LPC_UART3->THR=buffer[i];
	        //  i++;
					//	}
						
						UART_TRANSMIT_STRING();
						
}

void UART_TRANSMIT_STRING()
{
	for(int i=0;buffer[i]!='\0';i++)
	{
		while(!(LPC_UART3->LSR&(0X20)));
			LPC_UART3->THR =buffer[i];
	}
}
void UART_TRANSMIT_STRING_HC()
{
	unsigned char STRING[100] = "HELLO\n\n\rFROM DESD\n\n\rUART IS WORKING\n\n\r";
	
	for(int i =0; STRING[i]!='\0';i++)
				{
					
					if(STRING[i]=='\n')
					{
																		while(!(LPC_UART3->LSR&(0X20)));
																		LPC_UART3->THR =0X0D;
					}
						
								
									while(!(LPC_UART3->LSR&(0X20)));
										LPC_UART3->THR = STRING[i];
								
				}
}