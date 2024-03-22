/*bai10
#pragma config FNOSC = PRI
#pragma config POSCMOD = HS
#pragma config JTAGEN = OFF
#pragma config WINDIS = OFF
#pragma config FWDTEN = OFF

#define FCY 8000000UL
#include "xc.h"
#include "libpic30.h"
#include "lcd.h"
#include "string.h"

int main(void){
    char chuoi[11] = "LTK is kute\0";
    int i,j,k;
    LCD_Initialize();
    while(1){
        char manhinh[16]="                ";
        for (i = 15; i >= 4; i--){\
            j = i;
            while (j <= 15){
                for (k = 0;k <= 15 - i; k++){
                    manhinh[j] = chuoi[k];
                    j++;
                }
            }
            LCD_ClearScreen();
            printf("%s",manhinh);
            __delay_ms(500);
        }
        for (i = 0; i <= 14; i++){
            for (j = 0; j < 15; j++){
                manhinh[j] = manhinh[j + 1];
            }
            manhinh[15]=' ';
            LCD_ClearScreen();
            printf("%s",manhinh);
            __delay_ms(500);
        }
    }
}*/
/*#pragma config FNOSC = PRI
#pragma config POSCMOD = HS
#pragma config JTAGEN = OFF

#include "xc.h"
#define FCY 8000000UL
#include "libpic30.h"

int main(void){
int sohang1 = 0;
int sohang2 = 0;
int tempt = 0;
int tong = 0;
TRISDbits.TRISD6 = 1;
TRISDbits.TRISD7 = 1;
TRISDbits.TRISD13 = 1;
#ifdef  __PIC24FJ1024GB610__
ANSDbits.ANSD6 = 0;
ANSDbits.ANSD7 = 0;
#endif 
TRISA = 0;
#ifdef  __PIC24FJ1024GB610__
ANSA = 0;
#endif
while(1){
if(!PORTDbits.RD6){
while(!PORTDbits.RD6);
sohang1++;
__delay_ms(100);
LATA = sohang1;
}

if(!PORTDbits.RD7){
LATA = 0;
while(!PORTDbits.RD7);
sohang2++;
__delay_ms(100);
LATA = sohang2;
}

if(!PORTDbits.RD13){
LATA = 0;
while(!PORTDbits.RD13);
tempt++;
__delay_ms(100);
}
switch(tempt)
{
case 1:
tong = sohang1 + sohang2;
__delay_ms(100);
break;
case 2:
sohang1 = 0;
sohang2 = 0;
tempt = 0;
LATA = tong;
__delay_ms(100);
break;
}
}
return 0;
}
*/

/*bai3
 * #pragma config FNOSC = PRI
#pragma config POSCMOD = HS
#pragma config JTAGEN = OFF

#include "xc.h"
#define FCY 8000000UL
#include "libpic30.h"
#include "lcd.h"

int main(void){
int sohang1 = 0;
int sohang2 = 0;
int tempt = 0;
int tong = 0;

TRISDbits.TRISD6 = 1;
TRISDbits.TRISD7 = 1;
TRISDbits.TRISD13 = 1;
#ifdef  __PIC24FJ1024GB610__
ANSDbits.ANSD6 = 0;
ANSDbits.ANSD7 = 0;
#endif 
TRISA = 0;
#ifdef  __PIC24FJ1024GB610__
ANSA = 0;
#endif
LCD_Initialize();
while(1){
    
if(!PORTDbits.RD6){
while(!PORTDbits.RD6);
sohang1++;
LCD_ClearScreen();
printf("A = %d\r\n",sohang1);
__delay_ms(100);
}

if(!PORTDbits.RD7){
while(!PORTDbits.RD7);
sohang2++;
LCD_ClearScreen();
printf("B = %d\r\n",sohang2);
__delay_ms(100);
}

if(!PORTDbits.RD13){
LATA = 0;
while(!PORTDbits.RD13);
tempt++;
__delay_ms(100);
}
switch(tempt)
{
case 1:
tong = sohang1 + sohang2;
__delay_ms(100);
break;
case 2:
sohang1 = 0;
sohang2 = 0;
tempt = 0;
LCD_ClearScreen();
printf("tong = %d\r\n",tong);
__delay_ms(100);
break;
}
}
return 0;
}*/
/*BAI4
 * #pragma config FNOSC = PRI
#pragma config POSCMOD = HS
#pragma config JTAGEN = OFF
#include "xc.h"
#define FCY 8000000UL
#include "libpic30.h"
#include "lcd.h"

void analogInit(){
#ifdef __PIC24FJ1024GB610__
AD1CON2bits.PVCFG = 0x0;
#else
AD1CON2bits.VCFG = 0x0;
#endif
AD1CON3bits.ADCS = 0xFF;
AD1CON1bits.SSRC = 0x0;
AD1CON3bits.SAMC = 0b10000;
AD1CON1bits.FORM = 0b00;
AD1CON2bits.SMPI = 0x0;
AD1CON1bits.ADON = 1;
}
uint16_t analogRead(int channel){
uint16_t i;
switch(channel){
case 4:
#ifdef __PIC24FJ1024GB610__
ANSBbits.ANSB4 = 1;
#else
AD1PCFGbits.PCFG4 = 0;
#endif
break;
case 5:
#ifdef __PIC24FJ1024GB610__
ANSBbits.ANSB5 = 1;
#else 
AD1PCFGbits.PCFG5 = 0;
#endif 
break;
}
AD1CHS = channel;
AD1CON1bits.SAMP = 1;
for (i = 0; i<1000;i++){
Nop();
}
AD1CON1bits.SAMP=0;
for(i=0;i<1000;i++){
Nop();
}
while (!AD1CON1bits.DONE);
return ADC1BUF0;
}
int main(void){
uint16_t adcResult;
TRISA = 0;
#ifdef __PIC24FJ1024GB610__
ANSA = 0;
#endif
analogInit ();
LCD_Initialize();
float nhietdo;
while(1)
{ 
LCD_ClearScreen();
adcResult=analogRead(4);
nhietdo = (1000.0*adcResult*3.3/1024.0 - 500.0)/10.0;
printf("nhiet do la %0.1f do C\r\n", nhietdo);
__delay_ms(500);
}
return 0;
}*/
/*BAI5
 * #pragma config FNOSC = PRI
#pragma config POSCMOD = HS
#pragma config JTAGEN = OFF
#include "xc.h"
#define FCY 8000000UL
#include "libpic30.h"
#include "lcd.h"

void analogInit(){
#ifdef __PIC24FJ1024GB610__
AD1CON2bits.PVCFG = 0x0;
#else
AD1CON2bits.VCFG = 0x0;
#endif
AD1CON3bits.ADCS = 0xFF;
AD1CON1bits.SSRC = 0x0;
AD1CON3bits.SAMC = 0b10000;
AD1CON1bits.FORM = 0b00;
AD1CON2bits.SMPI = 0x0;
AD1CON1bits.ADON = 1;
}
uint16_t analogRead(int channel){
uint16_t i;
switch(channel){
case 4:
#ifdef __PIC24FJ1024GB610__
ANSBbits.ANSB4 = 1;
#else
AD1PCFGbits.PCFG4 = 0;
#endif
break;
case 5:
#ifdef __PIC24FJ1024GB610__
ANSBbits.ANSB5 = 1;
#else 
AD1PCFGbits.PCFG5 = 0;
#endif 
break;
}
AD1CHS = channel;
AD1CON1bits.SAMP = 1;
for (i = 0; i<1000;i++){
Nop();
}
AD1CON1bits.SAMP=0;
for(i=0;i<1000;i++){
Nop();
}
while(!AD1CON1bits.DONE);
return ADC1BUF0;
}
int main(void){
uint16_t adcResult;
TRISA = 0;
#ifdef __PIC24FJ1024GB610__
ANSA = 0;
#endif
analogInit ();
LCD_Initialize();
while(1)
{ 
LCD_ClearScreen();
adcResult=analogRead(5);
printf("R = %0.3f\r\n kOhm", adcResult*10.0/1024);
__delay_ms(100);
}
return 0;
}*/
//BAI6
/*#pragma config FNOSC = PRI
#pragma config POSCMOD = HS
#pragma config JTAGEN = OFF
#pragma config FWDTEN = OFF
#pragma config WINDIS = OFF

#include "xc.h"
#define FCY 8000000UL
#include "libpic30.h"
volatile uint16_t Timer1_flag = 0;
void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void){
    IFS0bits.T1IF = 0;
    Timer1_flag = 1;
}
void Timer1_Init(uint16_t value)
{
    T1CONbits.TON = 0;
    T1CONbits.TCKPS = 0x03;
    T1CONbits.TCS = 0;
    PR1 = value;
    IPC0bits.T1IP = 1;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    
}
void Timer1_Start ()
{
    T1CONbits.TON =1;
    
}
int main(void) {
        uint16_t sec = 0;
        int s=0;
        int min=0;
        int h=0;
    TRISA = 0;
#ifdef __PIC24FJ1024GB610__
    ANSA = 0;
#endif
    Timer1_Init(15625);
    Timer1_Start ();
    LCD_Initialize();
    while (1)
    {
       
        
        if(Timer1_flag)
        {
            sec++;
            s = sec;
            if(s > 59)
            {
                sec = 0;
                s = 0;
                min++;
                if(min > 59)
                {
	               min = 0;
                   h++;
                }
                if(h==24)
                {
                   h=0;
                }
            }
            LCD_ClearScreen();
            printf("Bay gio la: \r\n");
            printf("%d:%d:%d\r\n", h, min, s);
            Timer1_flag = 0;
        }
    }
    return 0;
}*/
//bai8
/*#pragma config FNOSC = PRI
#pragma config POSCMOD = HS
#pragma config JTAGEN = OFF
#pragma config FWDTEN = OFF
#pragma config WINDIS = OFF

#include "xc.h"
#define FCY 8000000UL
#include "libpic30.h"
volatile uint16_t Timer1_flag = 0;
void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void){
    IFS0bits.T1IF = 0;
    Timer1_flag = 1;
}
void Timer1_Init(uint16_t value)
{
    T1CONbits.TON = 0;
    T1CONbits.TCKPS = 0x03;
    T1CONbits.TCS = 0;
    PR1 = value;
    IPC0bits.T1IP = 1;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    
}
void Timer1_Start ()
{
    T1CONbits.TON =1;
    
}
int main(void) {
    uint16_t sec = 0;
    TRISDbits.TRISD6 = 1;
#ifdef __PIC24FJ1024GB610__
    ANSDbits.ANSD6 = 0;
#endif
    Timer1_Init(15625);
    Timer1_Start ();
    LCD_Initialize();
    while (1)
    {
        int s;
        if(!PORTDbits.RD6)
        {
               while(!PORTDbits.RD6);
               while(1)
               {
                       if(Timer1_flag)
                       {
                               sec++;
                               s = sec;
                               LCD_ClearScreen();
                               printf("Time: %d giay\r\n", sec);
                               Timer1_flag = 0;
                       }
                       if(!PORTDbits.RD6)
                       {
                               while(!PORTDbits.RD6);
                               while(1);
                       }
               }
        }
    }
    return 0;
}*/
//bai1thanh





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

//bai 9

/*
 * File:   Bai 1.c
 * Author: Richard
 *
 * Created on Ngày 18 tháng 5 n?m 2018, 15:22
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
#include "lcd.h"

volatile uint16_t Timer1_flag = 0;
void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void){
    IFS0bits.T1IF = 0;
    Timer1_flag = 1;
}
void Timer1_Init(){
    T1CONbits.TON = 0;
    T1CONbits.TCKPS = 0x03;
    T1CONbits.TCS = 0;
    
    IPC0bits.T1IP = 1;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
}
void Timer1_Start(){
    T1CONbits.TON = 1;
    
}
void  Timer1_Update(uint16_t adcResult)
{
        float time1 = ((adcResult*1.0*10/1024.0) * 0.45 + 0.5);
        float time2 = 1.0 * 2 * 256 / FCY;
        float time = time1 / time2;
        PR1=time;
        LCD_ClearScreen();
        printf("%u",PR1);
}
void analogInit(){
#ifdef __PIC24FJ1024GB610__
    AD1CON2bits.PVCFG = 0x0;
#else
    AD1CON2bits.VCFG = 0x0;
#endif
    AD1CON3bits.ADCS = 0xff;
    AD1CON1bits.SSRC = 0x0;
    AD1CON3bits.SAMC = 0b10000;
    AD1CON1bits.FORM = 0b00;
    AD1CON2bits.SMPI = 0x0;
    AD1CON1bits.ADON = 1;
}
uint16_t analogRead (int channel){
    uint16_t i;
    switch(channel){
        case 4:

    AD1PCFGbits.PCFG4 = 0;

    break;
        case 5:



            AD1PCFGbits.PCFG5 = 0;

            break;
    }
    AD1CHS = channel;
    AD1CON1bits.SAMP = 1;
    for (i = 0; i < 1000; i++){
        Nop();
    }
    AD1CON1bits.SAMP = 0;
    for (i = 0; i < 1000; i++){
        Nop();
    }
    while(!AD1CON1bits.DONE);
    return ADC1BUF0;
}
int main(void){
    uint16_t adcResult;
    uint16_t sec=0;
    TRISA = 0;

    analogInit();
    LCD_Initialize();
    Timer1_Init();
    LATA=255;
     Timer1_Start();
     
    while(1){
        
        adcResult = analogRead(5);
        Timer1_Update(adcResult);
        
        if (Timer1_flag)
            
        {
            if (LATA==255)
            {
                LATA=0;
            }
            else LATA = 255;
                
           Timer1_flag = 0;
        }
         
    }
     return 0;
}
