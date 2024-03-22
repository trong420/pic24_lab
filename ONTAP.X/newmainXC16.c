/*
 * File:   newmainXC16.c
 * Author: dell
 *
 * Created on June 8, 2018, 8:17 PM
 */
/*bai1
#pragma config FNOSC = PRI
#pragma config POSCMOD = HS
#pragma config JTAGEN = OFF
#pragma config WINDIS = OFF
#pragma config FWDTEN = OFF

#include "xc.h"
#define FCY 8000000UL
#include "stdio.h"
#include "libpic30.h"

int main(void){
    TRISA=0;
#ifdef __PIC24FJ1024GB610__
    ANSA =0;
#endif
    int i;
    while (1){
        i=0;
        while(1){
            LATA =0x05;
            __delay_ms(500);
            while(1){
                if(i==10){
                    break;
                }
                LATA =LATA *2;
                __delay_ms(500);
                i=i+1;
                if(LATA ==0xA0)
                {
                    while(1){
                        if(i==10){
                            break;
                        }
                        LATA=LATA/2;
                        __delay_ms(500);
                        i=i+1;
                        if(LATA == 0x05){
                            break;
                        }
                    }
                }
            }
            break;
        }
        int temp1 =0, temp2 =0;
        int i =0;
        while (1)
        {
            if(i==10){
                break;
            }
            if((temp1!=0 && temp2!=0)&&(temp1/2!=0)){
                temp1=temp1/2;
                temp2=temp2*2;
            }
            else{
                if(temp1==1||temp1==0){
                    temp1 = 0x80;
                    temp2 = 0x01;
                }
            }
            LATA = temp1+temp2;
            __delay_ms(500);
            i=i+1;
        }
    }
    return 0;
}*/
#pragma config FNOSC = PRI
#pragma config POSCMOD =HS
#pragma config JTAGEN =OFF
#pragma config WINDIS =OFF
#pragma config FWDTEN =OFF

#include "xc.h"
#define FCY 8000000UL
#include "stdio.h"
#include "libpic30.h"

int main(void){
    int sohang1 =0;
    int sohang2 =0;
    int tempt =0;
    int tong =0;
    
    TRISDbits.TRISD6 =1;
    TRISDbits.TRISD7 =1;
    TRISDbits.TRISD13=1;
#ifdef __PIC24FJ1024GB610__
    ANSDbits.ANSD6=0;
    ANSDbits.ANSD7 =0;
#endif
    TRISA = 0;
#ifdef __PIC24FJ1024GB610__
    ANSA =0;
#endif
    while (1){
        if(!PORTDbits.RD6){
            while(!PORTDbits.RD6)
                sohang1++;
            __delay_ms(500);
            LATA =sohang1;
        }
        if(!PORTDbits.RD7 ){
            LATA =0;
            while(!PORTDbits.RD7);
            sohang2++;
            __delay_ms(500);
            LATA = sohang2;
        }
        if(!PORTDbits.RD13){
            LATA =0;
            while(!PORTDbits.RD13);
            tempt++;
            __delay_ms(500);
        }
        switch(tempt)
        {
            case 1:
                tong =sohang1 +sohang2;
                __delay_ms(500);
                break;
            case 2:
                sohang1 =0;
                sohang2= 0;
                tempt = 0;
                LATA=tong;
                __delay_ms(500);
                break;
        }
    }
    
           
            
      return 0;      
}

