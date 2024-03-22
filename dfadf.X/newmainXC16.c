/*
 * File:   newmainXC16.c
 * Author: dell
 *
 * Created on May 26, 2018, 12:12 PM
 */


#pragma config FNOSC = PRI
#pragma config POSCMOD = HS 
#pragma config JTAGEN = OFF
#pragma config WINDIS = OFF
#pragma config FWDTEN = OFF

#include "xc.h"
#define FCY 8000000UL
#include "libpic30.h"


int main(void){
	int count = 0;
	TRISA = 0;
    LATA = 0b1010000;
	while(1){
        if(count < 5){
            LATA = LATA >> 1;
        }
    }
	return 0;
}
		
