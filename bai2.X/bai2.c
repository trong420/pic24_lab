#pragma config FNOSC = PRI
#pragma config POSCMOD = HS
#pragma config JTAGEN = OFF
#pragma config WINDIS = OFF
#pragma config FWDTEN = OFF

#include "string.h"
#define FCY 8000000UL
#include "xc.h"
#include "libpic30.h"
#include "lcd.h"


int main(void){
    LCD_Initialize();
    LCD_ClearScreen();
    int i = 0,j = 0;
    char LTK[19] = "LTK IS cutehhh     ";    
    while(1){
       LCD_ClearScreen();
        char temp;
        temp = LTK[0];
        for ( j = 0; j < 19; j++){
            LTK[j] = LTK[j+1];
        }
        LTK[18] = temp;
        for(i = 0; i < 16; i++){
            printf("%c", LTK[i]);
        }
 __delay_ms(200);
}
    return 0;
}