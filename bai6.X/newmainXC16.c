#pragma config FNOSC = PRI
#pragma config POSCMOD = HS
#pragma config JTAGEN = OFF
#pragma config WINDIS = OFF
#pragma config FWDTEN = OFF

#include "xc.h"
#define FCY 8000000UL
#include "libpic30.h"
#include "lcd.h"

volatile uint16_t Timer1_flag = 0;
void __attribute__ ((__interrupt__,auto_psv)) _T1Interrupt(void){
    IFS0bits.T1IF = 0;
    Timer1_flag =1; 
}
void Timer1_Init(uint16_t value){
    T1CONbits.TON = 0;
    T1CONbits.TCKPS = 0x03;
    T1CONbits.TCS = 0;
    PR1 = value;
    IPC0bits.T1IP =1;
    IFS0bits.T1IF =0;
    IEC0bits.T1IE =1;
}
void Timer1_Start() {
    T1CONbits.TON =1;
}
int main (void){
    TRISA = 0;
    int sec =0 ;
    int min = 0;
    int hour = 0;
    LCD_Initialize ();
    Timer1_Init(15625);
    Timer1_Start();
    while(1){
        if(Timer1_flag)
        {
            LCD_ClearScreen();
            sec++;
            if(sec==60)
            {
                min++;
                sec=0;
            }
            if(min==60)
            {
                hour++;
                min=0;
            }
            if(hour==24)
            {
                hour=0;
            }
            printf("%d:%d:%d",hour,min,sec);
            __delay_ms(500);
            Timer1_flag =0;
        }
    }
    return 0;
}
               
           
