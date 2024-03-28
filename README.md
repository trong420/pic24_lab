
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


```bash

```


```bash

```

![image](https://github.com/trong420/pic24_lab/assets/90754954/91b0d678-8e86-4eea-9e71-1103baaf6b9e)

