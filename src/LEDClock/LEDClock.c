#define offNumber 10
#define offPosition 4
#define startTimerValue 64560
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

char hours=0, minutes=0, seconds=0, buff=0;
char number[11]={64, 121, 36, 48, 25, 18, 2, 120, 0, 16, 127};
char position[5]={1, 2, 4, 8, 0};

ISR( TIMER1_OVF_vect )
{
	TCNT1 = startTimerValue;
	buff++;
}

int main(void) {
	setupPinout();
	setupTimer();
	while(1==1){
		if (seconds!=buff){
			seconds=buff;
		}
		if (seconds>=60){
			minutes++;
			seconds=0;
			buff=0;
		}
		if (minutes>=60){
			hours++;
			minutes=0;
		}
		if (hours>=24){
			seconds=0;
			minutes=0;
			hours=0;
		}
		print();
	}
	return 0;
}

void setupPinout(){
	DDRB=255;
	DDRD=15;
}

void setupTimer(){
	TCCR1B = (1<<CS12)|(0<<CS11)|(1<<CS10);
	TIMSK |= (1<<TOIE1);
	TCNT1 = startTimerValue;
	sei();
}

char takeFirst(char date){
	if(date<10)
	return date;
	return date%10;
}

char takeSecond(char date){
	if(date<10)
	return 0;
	return date/10;
}

void print(){
	printChar(3, takeFirst(minutes));
	turnOff();
	printChar(2, takeSecond(minutes));
	turnOff();
	printChar(1, takeFirst(hours));
	turnOff();
	printChar(0, takeSecond(hours));
	turnOff();								
}

void printChar(char p, char n){
	PORTD=position[p];
	PORTB=number[n];
}

void turnOff(){
	PORTD=position[offPosition];
	PORTB=number[offNumber];
}