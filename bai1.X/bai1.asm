    #pragma config FNOSC = PRI
    #pragma config POSCMOD = HS
    #pragma config JTAGEN = OFF
    #pragma config WINDIS = OFF
    #pragma config FWDTEN = OFF
    
    #define FCY 8000000UL
    #include "xc.h"
    #include "stdio.h"
    #include "libpic30.h"
    
    int main(void){
    TRISA = 0;
    #ifdef __PIC24FJ1024GB610__
    ANSA = 0;
    #endif
    
    int i;
    while (1){
	i=0;
	while (1){
	    LATA = 0x05;
	    __delay_ms(500);
	    while(1){
	    if(i==10){
		break;
		}
		LATA = LATA *2;
		__delay_ms(500);
		i=i+1;
		if(LATA = 0xA0){
		    while(1){
			if(i==10)
			{
			break;
			}
			LATA =LATA /2;
			i=i+1;
			if(LATA = 0x05)
			{
			break;
			}
			}
			}
			}
			break;
			}
		int temp1 = 0, temp2 =0;
		i=0;
		if
		
			
		
    
  


