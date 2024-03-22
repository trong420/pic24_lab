/*
 * File:   newmainXC16.c
 * Author: Admin
 *
 * Created on January 1, 2009, 12:07 AM
 */
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
    int i;
    while(1){
        i = 0;
    while(1){
        LATA = 0x05;
        __delay_ms(500);
        while(1) {
            if(i == 10){
                break;
            }
            LATA = LATA * 2;
            __delay_ms(500);
            i = i + 1;
            
            if(LATA == 0xA0)
            { 
                while(1) {
                    if(i==10)
                    {
                        break;
                    }
                LATA = LATA / 2;
                __delay_ms(500);
                i = i + 1;
                if(LATA == 0x05)
                {
                    break;
                }
                }
            
            }
        }
        break;
    }
    int temp1 = 0, temp2 = 0;
    i = 0;
    while(1){
        if (i == 10){
            break;
        }
        if ((temp1 != 0 && temp2 != 0)&&(temp1/2 != 0)){
        temp1 = temp1 / 2;
        temp2 = temp2 * 2;
        }
        else{
            if(temp1==1||temp1==0){
            temp1 = 0x80;
            temp2 = 0x01;
            }
        }
        LATA = temp1 + temp2;
        __delay_ms(500);
        i = i + 1;
    }
    }
     return 0;
}
