/*
 * GccApplication1.c
 *
 * Created: 2022-12-03 오전 10:29:14
 * Author : chymh
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define T1_START 62411
#define AD_CHECK 0x10
#define AD_CH0 0x00
#define AD_CH1 0x01
#define MAX_PWM3 100
#define _9600BPS 95

int fail_count;
int Data;
int clear; // 잠금 해제 성공 변수
int set_pwd; // 초기 비밀번호 유무 판별
int start_value; // 초기 벨루값
int a1,a2,a3,a4; // 잠금해제 입력 변수
int b1,b2,b3,b4; // 초기설정 비밀번호 입력 변수
char FND_TABLE[5] = {0x3F , 0x06,0x5B,0x4F,0x66}; 
int timer_count;
	

ISR(TIMER1_OVF_vect){
	
	
	
	if (ADC < 500)Data=100; // 주변이 어둘울 때 PWM 밝기 100
	else if (ADC >= 750)Data=0; // 주변이 밝을 때 PWM 밝기 0
	ADCSRA=0xC7;
	OCR3A = Data;
	// 잠금해제 되었을때 PB0부터7까지 불을 깜빡거림
	if(clear==1){
		TCNT1 = T1_START;
		PORTB ^=0xFF;
		timer_count+=1;
		if(timer_count>=10){
			timer_count=0;
			clear=0; // 잠금변수 초기화
		}
	}

}	

ISR(USART1_RX_vect)
{
	char tmp;
	
	tmp = UDR1;
	
	if(tmp == '0') PORTB &= ~0x01;
	else if(tmp == '1') PORTB &= ~0x02;
	else if(tmp == '2') PORTB &= ~0x04;
	else if(tmp == '3') PORTB &= ~0x06;
	else if(tmp == '4') PORTB &= ~0x08;
	else if(tmp == '5') PORTB &= ~0x10;
	else if(tmp == '6') PORTB &= ~0x20;
	else if(tmp == '7') PORTB &= ~0x40;
	else if(tmp == '8') PORTB &= ~0x80;
	else if(tmp == '1') PORTB |= ~0xFF;
}





void Init_Serial_1(void)
{
	UBRR1H = 0;
	UBRR1L = _9600BPS;
	UCSR1A = 0x00;
	UCSR1B = 0x98;
	UCSR1C = 0x06;
}

void TX1_char(char data)
{
	while((UCSR1A & 0x20) == 0x00);
	UDR1 = data;
}

void TX1_string(char*string)
{
	while(*string != '\0'){
		TX1_char(*string);
		string++;
	}
}


	
	
	
	



void Init_IOport(void){
	DDRB=0xFF;
	PORTB=0xFF;
	
	DDRC = 0xFF;
	PORTC = 0xFF;
	
	DDRD=0xFF;
	PORTD = 0x0F;
	
	
}
void Init_Interrupt(void){
	SREG=0x80;
	EIMSK=0xF0;
	EICRB=0xAA;
	
	TCCR1A=0x00;
	TCCR1B = 0x05;
	TIMSK = 0x04;
	DDRE=0x0F;
	PORTE=0xFF;
	TCNT1 = T1_START;
}
void Init_PWM3_port(void)
{
	TCCR3A = 0xFE;
	TCCR3B = 0x11;
	ICR3 = MAX_PWM3;
	
}
void Output_PWM3A(int data)
{
	OCR3A = data;
}
ISR(INT4_vect){
	
	//초기 설정모드
	if (set_pwd==0){
		if (b1 ==0){
			b1=1;
		}
		else if (b1 != 0 && b2==0 ){
			b2=1;
		}
		else if (b1 !=0 && b2 !=0 && b3==0){
			b3=1;
		}
		else if (b1 !=0 && b2 !=0 && b3 != 0 && b4==0){
			b4=1;
		}
		
	}
	// 잠금해제 모드
	if (set_pwd==1){
	if (a1 ==0){
		a1=1;
	}
	else if (a1 != 0 && a2==0 ){
		a2=1;
}
	else if (a1 !=0 && a2 !=0 && a3==0){
		a3=1;
	}
	else if (a1 !=0 && a2 !=0 && a3 != 0 && a4==0){
		a4=1;
	}
	}
	}
ISR(INT5_vect){
		//초기 설정모드
		if (set_pwd==0){
			if (b1 ==0){
				b1=2;
			}
			else if (b1 != 0 && b2==0 ){
				b2=2;
			}
			else if (b1 !=0 && b2 !=0 && b3==0){
				b3=2;
			}
			else if (b1 !=0 && b2 !=0 && b3 != 0 && b4==0){
				b4=2;
			}
			
		}
		// 잠금해제 모드
		if (set_pwd==1){
			if (a1 ==0){
				a1=2;
			}
			else if (a1 != 0 && a2==0 ){
				a2=2;
			}
			else if (a1 !=0 && a2 !=0 && a3==0){
				a3=2;
			}
			else if (a1 !=0 && a2 !=0 && a3 != 0 && a4==0){
				a4=2;
			}
		}
}
ISR(INT6_vect){
	//초기 설정모드
	if (set_pwd==0){
		if (b1 ==0){
			b1=3;
		}
		else if (b1 != 0 && b2==0 ){
			b2=3;
		}
		else if (b1 !=0 && b2 !=0 && b3==0){
			b3=3;
		}
		else if (b1 !=0 && b2 !=0 && b3 != 0 && b4==0){
			b4=3;
		}
		
	}
	// 잠금해제 모드
	if (set_pwd==1){
		if (a1 ==0){
			a1=3;
		}
		else if (a1 != 0 && a2==0 ){
			a2=3;
		}
		else if (a1 !=0 && a2 !=0 && a3==0){
			a3=3;
		}
		else if (a1 !=0 && a2 !=0 && a3 != 0 && a4==0){
			a4=3;
		}
	}
}

ISR(INT7_vect){
//초기 설정모드
if (set_pwd==0){
	if (b1 ==0){
		b1=4;
	}
	else if (b1 != 0 && b2==0 ){
		b2=4;
	}
	else if (b1 !=0 && b2 !=0 && b3==0){
		b3=4;
	}
	else if (b1 !=0 && b2 !=0 && b3 != 0 && b4==0){
		b4=4;
	}
	
}
// 잠금해제 모드
if (set_pwd==1){
	if (a1 ==0){
		a1=4;
	}
	else if (a1 != 0 && a2==0 ){
		a2=4;
	}
	else if (a1 !=0 && a2 !=0 && a3==0){
		a3=4;
	}
	else if (a1 !=0 && a2 !=0 && a3 != 0 && a4==0){
		a4=4;
	}
}
}


int main(void)
{	Init_IOport();
	Init_Interrupt();
	ADMUX = AD_CH1;
	
	Init_PWM3_port();
	Output_PWM3A(0);

	Init_Serial_1();


	
	
	

   /* Replace with your application code */
		while(10000){
			
		if (set_pwd==0){
			while(10000){
			if(b1!=0){
				PORTD &= 0x0F;
				PORTC = ~FND_TABLE[b1];
				PORTD |= 0x10;
			}
			if (b2!=0){
				PORTD &= 0x0F;
				PORTC = ~FND_TABLE[b2];
				PORTD |= 0x20;
			}
			if (b3!=0){
				PORTD &= 0x0F;
				PORTC = ~FND_TABLE[b3];
				PORTD |= 0x40;
			}
			if (b4!=0){
				PORTD &= 0x0F;
				PORTC = ~FND_TABLE[b4];
			PORTD |= 0x80;}
			if (b1!=0 && b2!=0 && b3!=0 && b4 != 0)
				break;}

		PORTD=0xF0;
		PORTC=~FND_TABLE[0];
		set_pwd=1;
		}
		
		
		
		
		else if (set_pwd == 1){
	    while(10000){
		    if(a1!=0){
			    PORTD &= 0x0F;
			    PORTC = ~FND_TABLE[a1];
			    PORTD |= 0x10;
		    }
		    if (a2!=0){
			    PORTD &= 0x0F;
			    PORTC = ~FND_TABLE[a2];
			    PORTD |= 0x20;
		    }
		    if (a3!=0){
			    PORTD &= 0x0F;
			    PORTC = ~FND_TABLE[a3];
			    PORTD |= 0x40;
		    }
		    if (a4!=0){
			    PORTD &= 0x0F;
			    PORTC = ~FND_TABLE[a4];
		    PORTD |= 0x80;}
			//비밀번호 다 입력되었을 때
			if (a1 != 0 && a2 != 0 && a3 !=0 && a4 !=0){
				break;}
				}
					}
					// 비밀번호 입력 완료후 잠금시도
	if (a1 != 0 && a2 != 0 && a3 !=0 && a4 !=0)
	{
					// 비밀번호 맞을 시 open
					if(a1==b1 && a2==b2 && a3==b3 && a4==b4){
						PORTD = 0xF0;
						PORTC=~FND_TABLE[0];
						TX1_string("Try : \r\n");
						TX1_string("Unlock: Correct password!\r\n"); // 잠금 해제 되었을 때 UART TEXT 전송
						a1=a2=a3=a4=0;
						clear=1;
						
						
					}
	//비밀번호 틀릴 시 fail
				else if (a1!=b1 || a2!=b2 || a3!=b3 || a4!=b4)
						{
							PORTD = 0xF0;
							PORTC=~FND_TABLE[0];
							a1=a2=a3=a4=0;
							fail_count+=1;
							if (fail_count>=3) {
								fail_count=0;
								TX1_string("Try : \r\n"); 
								TX1_string("Someone's trying Please check!\r\n"); // 3번 틀렸을 경우 UART TEXT 전송
							}
							
						}
		}
	}

	


}





