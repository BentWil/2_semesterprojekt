/*
 * USARTandMotor.c
 *
 * Created: 05-04-2024 19:57:19
 * Author : magnu
 */ 


#define F_CPU 19300000UL //20MHz


#include <avr/io.h>
#include <util/delay.h>


void send(uint8_t c) {
	while (!( UCSR1A & (1<<UDRE1))); // Wait until UART is ready to send
	UDR1 = c;                       // Send data
}

int main(void)
{
	
	// U A R T 
	UBRR1H = 0;
	UBRR1L = 125; // 125 works			 X_baud = F_CPU/(16 * 9600) - 1  calculate X for baudrate
	UCSR1B |= 1 << TXEN1;	// enable transmit 
	UCSR1B |= 1 << RXEN1;	// enable recieve
	DDRD |= 1<< 3; // set D3 as output
	
	// A D C
	ADMUX = 0;	//clear admux, bit4:0 selects A0 as input.
	ADMUX |= (1<<ADLAR);	// use full ADCH and two bits in ADCL
	ADMUX |= (1<<REFS0);	// use vcc (5v) as ref
	
	ADCSRA = (1<<ADEN);	//Enable ADC
	ADCSRA |= (0b111<<ADPS0); 	// use div by 128 to get 156 kHz (ish)
	
	PORTA &= ~1; // Disable pullup since analog input
	
	
	// M O T O R 
	DDRD |= 1<<5; // set PD5 (PMW M1) to output
	DDRC |= 1<<2; // set PC2 (DIR M1) to output
	DDRA &= ~1;  // Clear PA0 (Iout M1) set M1 as input 
	

	

	
	
	
	// L E D
	DDRB |= 1<<1;	// set PB1 LED as output
	PORTB &= ~(1<<1); // clear LED
	
	
	unsigned char ch;
	
	
    while (1) 
    {
	

	
 
		while(!(UCSR1A&(1<<RXC1)))  //Wait for recieve complete
		{
			ADCSRA |= (1<<ADSC); //start conversion
			while( ADCSRA & (1<<ADSC));  //wait
			
			send(ADCH);
			_delay_ms(1000);
			
		}; 
		
			
		ch = UDR1;
		if (ch == 'b'){		// turn on LED
			PORTB |= (1<<1);
		}
		else if(ch == 'e'){ // turn off LED
			PORTB &= ~(1<<1);
		}
		else if(ch == 'o'){		//open gripper
			PORTB |= (1<<1);		// LEDon
			PORTC &= ~(1<<2);		// set direction to open
			PORTD |= 1<<5;			//turn on motor	
			
			_delay_ms(1000);		//wait
			//wait for current to rise
			 
			while(ADCH > 0x73)  //experimental value 0x8c samle until over
			{
				 
				 ADCSRA |= (1<<ADSC); //start conversion
				 while( ADCSRA & (1<<ADSC));  //wait for ADC complete
				 
				 send(ADCH);
				 _delay_ms(10);
			}
			PORTC |= (1<<2);		// reverse direction (faster stop)
			PORTD &= ~(1<<5);		//turn off motor
			PORTB &= ~(1<<1);		//LEDoff
			
		}
		else if(ch == 'c'){		// closegripper
			PORTB |= (1<<1);		// LEDon
			PORTC |= (1<<2);		// set direction to close
			PORTD |= 1<<5;			//turn on motor
			
			 _delay_ms(1000);		//wait
									//wait for current to rise
			
			while(ADCH < 0x8b)  //experimental value 0x8c samle until over
			{
				
				ADCSRA |= (1<<ADSC); //start conversion
				while( ADCSRA & (1<<ADSC));  //wait for ADC complete 
				
				send(ADCH);
				_delay_ms(10);	
			}
			
			PORTC &= ~(1<<2);		// reverse direction
			PORTD &= ~(1<<5);		// trun off motor
			PORTB &= ~(1<<1);		// LEDoff
		}
		else if (ch == 'B'){		// turn on motor (for debug)
			PORTD |= 1<<5;
		}
		else if(ch == 'E'){			//turn off motor (for debug)
			PORTD &= ~(1<<5); 
		}
		else if (ch == 'C'){		//set motor to close dir (for debug)
			PORTC |= (1<<2);
		}
		else if(ch == 'O'){			//set motor to open dir (for debug)
			PORTC &= ~(1<<2);
		}
		
		
		
    }
}


