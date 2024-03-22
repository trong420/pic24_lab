    #pragma config FNOSC =PRI
    #pragma congfig  POSCMOD = HS
    #pragma config JTAGEN =OFF
    
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
    AD1CON3bits.SAMC = 0b1000;
    AD1CON1bits.FORM = 0b00;
    AD1CON2bits.SMPI = 0x0;
    AD1CON1bits.ADON = 1;
    }
    uint16_t analogRead(int channel) {
    uint16_t i;
    switch (channel) {
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
    AD1CON1bits. SAMP =1;
    for (i=0;i<1000;i++)
    {
    Nop();
    }
    AD1CON1bits.SAMP = 0;
    for (i=0; i<1000; i++)
    {
    Nop();
    }
    while (!AD1CON1bits.DONE);
    return ADCBUF0;
    }
    
    int main(void){
    uint16_t adcResult;
    TRISA = 0;
    #ifdef __PIC24FJ1024GB610__
    ANSA = 0;
    #endif
    analogInit();
    LCD_Initialize();
    float nhietdo;
    while (1)
    {
    LCD_ClearScreen();
    adcResult = analogRead (4);
    nhietdo = (1000.0 * adcResult * 3.3/1024.0 - 500.0)/10.0;
    printf("nhiet do la %0.1f do C\r\n", nhietdo);
    __delay_ms(500);
    }
    return 0;
    }
    
    
    
