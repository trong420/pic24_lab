
<div align="center">

<h1>PIC24 Microcontrollers with MPLAB</h1>
</div>


**LAB 1**
- Code to read the value from push buttons S3 and S4. When S3 is pressed, it will count up, S4
If pressed, the count will count down and the count value will be output to the LED / Code để đọc giá trị từ nút nhấn S3 và S4, khi S3 được nhấn thì sẽ đếm lên, S4
được nhấn thì sẽ đếm xuống và giá trị đếm sẽ được xuất ra LED.

```c
void delayms(unsigned t) {
  T1CON = 0x8000;
  while (t--) {
    TMR1 = 0;
    while (TMR1 < 2000);
  }
}
int main() {
  TRISA = 0;
  TRISDbits.TRISD6 = 1;
  TRISDbits.TRISD13 = 1;
  while (1) {
    while (PORTDbits.RD6 == 0) {
      if (PORTDbits.RD6 == 0) {
        PORTA = 0;
        while (PORTDbits.RD13 != 0) {
          PORTA = PORTA++;
          delayms(1000);
        }
      }
    }
    while (PORTDbits.RD13 == 0) {
      if (PORTDbits.RD13 == 0) {
        PORTA = 0;
        while (PORTDbits.RD6 != 0) {
          PORTA = PORTA--;
          delayms(1000);
        }
      }
    }
  }
}
```

- Simulation results with proteus after compiling from MPLAB / Kết quả mô phỏng với proteus sau khi biên dịch từ MPLAB

S3 presses the led to count up in binary form from D1 to D8 / S3 nhấn led đếm lên theo kiểu nhị phân từ D1 đến D8
![image](https://github.com/trong420/pic24_lab/assets/90754954/256d6e01-0b31-4d75-b4df-9645efccc64e)



S4 press the led to count down starting from 1111 1111 to 0000 0000 / S4 nhấn led đếm xuống bắt đầu từ 1111 1111 đến 0000 0000

![image](https://github.com/trong420/pic24_lab/assets/90754954/f5c777df-cf0f-4481-87b6-782fdbf83c5b)




- Code to read the value from push buttons S3 and S4, when S3 is pressed, the LED will gradually lighten, when S4 is pressed, the LED will gradually darken. / Code để đọc giá trị từ nút nhấn S3 và S4, khi S3 được nhấn thì LED sẽ sáng dần, S4 được nhấn thì LED sẽ tối dần.

```c
void delayms(unsigned t) {
  T1CON = 0x8000;
  while (t--) {
    TMR1 = 0;
    while (TMR1 < 2000);
  }
}

void sangdan() {
  unsigned char a;
  PORTA = 0;
  for (a = 0; a < 8; a++) {
    PORTA = (0x01 << a) | PORTA;
    delayms(500);
  }
}

void toidan() {
  unsigned char a;
  PORTA = 0;
  for (a = 0; a < 8; a++) {
    PORTA = (0xFF << a) | 0;
    delayms(500);
  }
}

int main() {
  TRISA = 0;
  TRISDbits.TRISD6 = 1;
  TRISDbits.TRISD13 = 1;
  while (1) {
    //S3
    while (PORTDbits.RD6 == 0) {
      if (PORTDbits.RD6 == 0) {
        PORTA = 0;
        while (PORTDbits.RD13 != 0) {
          sangdan();
          delayms(1000);
        }
      }
    }
    //S4
    while (PORTDbits.RD13 == 0) {
      if (PORTDbits.RD13 == 0) {
        PORTA = 0;
        while (PORTDbits.RD6 != 0) {
          toidan();
          delayms(1000);
        }
      }
    }
  }
}
```

S4 presses 8 LEDs to light up and gradually darken from D1 to D8 / S4 nhấn 8 led sáng hết và tối dần từ D1 tới D8
![image](https://github.com/trong420/pic24_lab/assets/90754954/43a21ef3-9727-48df-aaed-3d3ba1b50857)

S3 press the led to gradually light up starting from D1 to D8 / S3 nhấn led sáng dần bắt đầu từ D1 đến D8
![image](https://github.com/trong420/pic24_lab/assets/90754954/7b6b44b2-6a06-4a26-99c1-452f702ff5e8)

**LAB2: TIMER**

- Code to let the system count up after 500 ms using Timer 2 in timing and output mode
LED output results. / Code để hệ thống đếm lên sau 500 ms sử dụng Timer 2 ở chế độ định thời, xuất
kết quả ra led.

```c
void Timer2_Init() {
  T2CON = 0x00;
  TMR2 = 0x00;
  PR2 = 31250;
  T2CONbits.TCS = 0;
  T2CONbits.TCKPS = 2;
  T2CONbits.TON = 1;
}
int main() {
  TRISA = 0;
  TRISDbits.TRISD6 = 1;
  while (1) {
    if (PORTDbits.RD6 == 0) {
      Timer2_Init();
      PORTA = 0x00;
      while (PORTDbits.RD6 == 0) {
        if (TMR2 == PR2) {
          PORTA = PORTA++;
          TMR2 = 0;
        }
      }
    }
  }
  return 0;
}
```

Suppose S3 presses the counter to delay 500ms with PR2 = 31250 and Prescale = 64 / Cho là S3 nhấn mạch đếm lên delay 500ms với PR2 = 31250 và Prescale = 64

![image](https://github.com/trong420/pic24_lab/assets/90754954/cce451cd-6682-4716-b3ac-be5683804087)


- The code is so that when pressing S3 once, the LED gradually brightens by 20%, and when it reaches maximum brightness, it still remains
Press it again and the LED will turn off and gradually light up corresponding to the number of presses of S3. /  Code để khi nhấn S3 1 lần thì LED sáng dần 20%, khi sáng cực đại mà vẫn nhấn nữa thì LED sẽ tắt rồi sáng dần lên tương ứng với số lần nhấn của S3.

```c
void Timer1_Init() {
  T1CON = 0x00;
  TMR1 = 0x00;
  PR1 = 100;
  T1CONbits.TCS = 0;
  T1CONbits.TGATE = 0;
  T1CONbits.TCKPS = 1;
  T1CONbits.TON = 1;
}
int c2(int a) {
  if (PORTDbits.RD6 == 0) {
    while (PORTDbits.RD6 == 0);
    a = a + 20;
    if (a > 100) {
      a = 0;
    }
  }
  if (TMR1 <= a) {
    PORTA = 0;
  }
  if ((TMR1 > a) && (TMR1 < 100)) {
    PORTA = 0xFF;
  }
  if (TMR1 == PR1) {
    TMR1 = 0;
  }
  return a;
}
int main() {
  TRISA = 0;
  PORTA = 0;
  TRISDbits.TRISD6 = 1;
  Timer1_Init();
  int led = 0;
  while (1) {
    led = c2(led);
  }
}
```

When pressing button S3, the LEDs increase in brightness by 20% due to simulation, so the change in brightness is not clearly visible. / Khi nhấn nút S3 các led tăng độ sáng 20% do mô phỏng nên không thấy rõ sự thay đổi của độ sáng.

![image](https://github.com/trong420/pic24_lab/assets/90754954/30ec05d8-c542-4cfc-b5a1-f8a4a2f5955b)


**LAB3: ADC**

- Code

```c
void initADC() {
  AD1PCFGbits.PCFG4 = 0;
  AD1CSSL = 0;
  AD1CON1 = 0x00E0;
  AD1CON2 = 0;
  AD1CON3 = 0x1F02;
  _ADON = 1;
}
int readADC(int ch) {
  AD1CHS = ch;
  _SAMP = 1;
  while (!_DONE == 1);
  return ADC1BUF0;
}
void Timer1_Init() {
  T1CON = 0x00;
  TMR1 = 0x00;
  PR1 = 62500;
  T1CONbits.TCS = 0;
  T1CONbits.TCKPS = 2;
  T1CONbits.TON = 1;
}
int main() {
  int a = 0;
  initADC();
  TRISA = 0xff00;
  float t = 0.0;
  Timer1_Init();
  float vout = 0.0;
  while (1) {
    if (TMR1 == PR1) {
      a = readADC(4);
      vout = (float)(a) * 3.3 / 1024;
      t = (vout - 0.5) * 100;
      PORTA = (int) t;
      TMR1 = 0;
    }
  }
  return 0;
}
```

Simulation on Proteus: Currently the bit string 11010 is equivalent to 26 degrees. Simulation above
board, multiply Vout by 3.3, not 5. / Mô phỏng trên Proteus: Hiện chuỗi bit 11010 tương đương 26 độ. Mô phỏng trên
board thì nhân Vout với 3.3 chứ không nhân 5.

![image](https://github.com/trong420/pic24_lab/assets/90754954/2f3caaf5-f2b5-4338-a314-6d3158527a41)


The simulation on the board shows a bit string of 11100 equivalent to 28 degrees Celsius due to the board
LED D6 is damaged so it does not appear / Mô phỏng trên board hiển thị chuỗi bit 11100 tương đương 28 độ C do board
LED D6 bị hư nên nó không hiện

![image](https://github.com/trong420/pic24_lab/assets/90754954/91b0d678-8e86-4eea-9e71-1103baaf6b9e)

**LAB4: INTERRUPT**

- Configure PIC24/32 to perform an interrupt on Timer1 to turn the LED on and off every 500ms / Cấu hình PIC24/32 để thực hiện ngắt trên Timer1 để bật tắt led sau mỗi 500ms

```c
void Timer1_Init(void) {
  T1CON = 0x00;
  TMR1 = 0x00;
  PR1 = 31250;
  _T1IP = 0x06;
  _T1IF = 0;
  _T1IE = 1;
  T1CONbits.TCS = 0;
  T1CONbits.TSYNC = 0;
  T1CONbits.TCKPS = 2;
  T1CONbits.TON = 1;
}
void _ISR _T1Interrupt(void) {
  _T1IF = 0;
  count++;
  PORTA = count;
}
void INT0_Interrupt_Init() {
  INTCON2bits.INT0EP = 1;
  _INT0IP = 5;
  _INT0IF = 0;
  _INT0IE = 1;
}
void _ISR _INT0Interrupt(void) {
  _INT0IF = 0;
  AD1CHS = 5;
  AD1CON1bits.SAMP = 1;
}
void main() {
  TRISA = 0;
  INT0_Interrupt_Init();
  Timer1_Init();
  while (1) {}
}
```
Because the Timer Interrupt is set to 0.5s, it will automatically count up every 0.5s (Prescale = 64, PR1 = 31250) without having to press the INT0 button. / Do đã set Timer Interrupt là 0.5s nên 0.5s thì nó sẽ tự đếm lên (Prescale = 64, PR1= 31250) không cân phải nhấn nút INT0.

![image](https://github.com/trong420/pic24_lab/assets/90754954/b06d8fb1-7f99-4e13-aed0-692fb73be2d8)



- Configure the PIC24/32 to perform an interrupt on the ADC to read the sensor value
temperature and record to LED / Cấu hình PIC24/32 để thực hiện ngắt trên ADC để đọc giá trị của cảm biến
nhiệt độ và ghi ra LED

```c
void INT0_Interrupt_Init() {
  INTCON2bits.INT0EP = 1;
  _INT0IP = 5;
  _INT0IF = 0;
  _INT0IE = 1;
}
void _ISR _INT0Interrupt(void) {
  _INT0IF = 0;
  AD1CHS = 4;
  AD1CON1bits.SAMP = 1;
}
void ADC_Init() {
  AD1PCFGbits.PCFG4 = 0;
  AD1CON1 = 0x00E0;
  AD1CSSL = 0;
  AD1CON2 = 0;
  AD1CON3 = 0x1F02;
  AD1CON1bits.ADON = 1;
  _AD1IP = 3;
  _AD1IF = 0;
  _AD1IE = 1;
}
int a;
float vout = 0.0;
float t = 0.0;
void _ISR _ADC1Interrupt(void) {
  _AD1IF = 0;
  a = ADC1BUF0;
  //a = readADC(4);
  vout = (float)(a) * 3.3 / 1024;
  t = (vout - 0.5) * 100;
  PORTA = (int) t;
}
void main() {
  TRISA = 0;
  INT0_Interrupt_Init();
  ADC_Init();
  while (1) {}
}
```

When adjusting the temperature sensor and pressing the INT0 button, the 2 LED images will change
37 degrees shows 100101 and 31 degrees shows 11110 / Khi chỉnh cảm biến nhiệt độ rồi nhấn nút INT0 sẽ thay đổi trên LED 2 hình là
37 độ hiện 100101 và 31độ hiện 11110

![image](https://github.com/trong420/pic24_lab/assets/90754954/a1775b26-2824-432e-bd85-c860a7222c45)

![image](https://github.com/trong420/pic24_lab/assets/90754954/45e0761c-ba23-4b2e-a7a3-4b793f395d32)


**LAB5: UART**

- Execute interrupt configuration every time a value is received for UART1(execute
on board) / Thực hiện cấu hình ngắt mỗi khi nhận được giá trị cho UART1(thực hiện
trên board)

```c
void U1_Interrupt_Init() {
  U1STAbits.URXISEL = 0;
  _U1RXIP = 4;
  _U1RXIF = 0;
  _U1RXIE = 1;
}
void _ISR _U1RXInterrupt(void) {
  _U1RXIF = 0;
  char c = U1RXREG;
  tr[index] = c;
  putU1(tr[index]);
  index++;
  if (index > BUF_SIZE)
    index = 0;
}
```


- Implement a UART configuration program so that every time the string “Hello” is received
from the PC, the string "My name is A" will be sent back, where A is the student's name. When recieved
The string is different from the string "Hello", then send back the string "I do not know". Note that interrupts are used
UART. Implement a UART and ADC configuration program so that each time the string “temperature?” is received. will send back the temperature value read from the temperature sensor. For example
If the temperature is 28ºC, the character string "28 degrees Celsius" will be sent to the PC. (simulation using UART2)
/ Thực hiện chương trình cấu hình UART để mỗi khi nhận được chuỗi “Hello”
từ PC thì sẽ gửi lại chuỗi “My name is A”, với A là tên sinh viên. Khi nhận được
chuỗi khác chuỗi “Hello”, thì gửi lại chuổi “I do not know”. Lưu ý có sử dụng ngắt
UART. Thực hiện chương trình cấu hình UART và ADC để mỗi khi nhận được chuỗi “temperature?” thì sẽ gửi lại giá trị nhiệt độ đọc được từ cảm biến nhiệt độ. Ví dụ
nhiệt độ là 28ºC thì sẽ gửi đến PC chuỗi kí tự là “28 doC”. (mô phỏng dùng UART2)

```c
void initU2(void) {
  U2BRG = BRATE;
  U2MODE = U_ENABLE;
  U2MODEbits.BRGH = 1;
  U2STA = U_TX;
  _TRISF13 = 0;
  _TRISF12 = 1;
  RTS = 1;
}
int putU2(int c) {
  while (CTS);
  while (U2STAbits.UTXBF);
  U2TXREG = c;
  return c;
}
void putsU2(char * s) {
  while ( * s)
    putU2( * s++);
}
char getU2(void) {
  RTS = 0;
  while (!U2STAbits.URXDA);
  return U2RXREG;
  RTS = 1;
}
void U2_Interrupt_Init() {
  U2STAbits.URXISEL = 0;
  _U2RXIP = 4;
  _U2RXIF = 0;
  _U2RXIE = 1;
}
void _ISR _U2RXInterrupt(void) {
  _U2RXIF = 0;
  char c = U2RXREG;
  tr[index] = c;
  putU2(tr[index]);
  index++;
  if (index > BUF_SIZE)
    index = 0;
  if (c == '\r') {
    if (strcmp(tr, "Hello\r") == 0) {
      putsU2("My name is TRONG\n\r");
    } else if (strcmp(tr, "temperature\r") == 0) {
      putsU2("Nhiet do: \r\n");
      int temp = (int)(temperature * 10);
      putU2(temp / 100 + 48);
      putU2((temp % 100) / 10 + 48);
      putU2('.');
      putU2((temp % 100) % 10 + 48);
      putsU2("doC\r\n");
    } else {
      putsU2("I don't know\n\r");
    }
    for (index = 0; index < BUF_SIZE; index++)
      tr[index] = '\0';
    index = 0;
  }
  PORTA = index;
}
char * getsU2(char * s, int len) {
  char * p = s;
  int cc = 0;
  do {
    * s = getU2();
    if (( * s == BACKSPACE) && (s > p)) {
      putU2(' ');
      putU2(BACKSPACE);
      len++;
      s--;
      continue;
    }
    if ( * s == '\n')
      continue;
    if ( * s == '\r')
      break;
    s++;
    len--;
  } while (len > 1);
  * s = '\0';
  return p;
}
void initADC() {
  AD1PCFGbits.PCFG4 = 0;
  AD1CON1 = 0x00E0;
  AD1CSSL = 0;
  AD1CON2 = 0;
  AD1CON3 = 0x1F02;
  AD1CON1bits.ADON = 1;
}
int readADC(int ch) {
  AD1CHS = ch;
  AD1CON1bits.SAMP = 1;
  while (!AD1CON1bits.DONE);
  return ADC1BUF0;
}
int main() {
  char s[BUF_SIZE];
  TRISA = 0;
  initU2();
  putsU2("THUC HANH VI DIEU KHIEN!\n\r");
  U2_Interrupt_Init();
  initADC();
  int t;
  while (1) {
    t = readADC(4);
    temperature = (3.3 * (float)(t) * 1000 / 1024 - 500) / 10;
  }
}
```

Enter hi -> I don't know, enter Hello -> My name is IN, enter
temperature -> 37do. / Nhập hi -> I don’t know, nhập Hello -> My name is TRONG, nhập
temperature -> 37do.

![image](https://github.com/trong420/pic24_lab/assets/90754954/8076be79-4cae-458b-b65b-e69670e7201c)





