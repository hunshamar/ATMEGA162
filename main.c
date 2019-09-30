
#ifndef F_CPU
#define F_CPU 4915200UL
#endif

#include <stdio.h>
#include <avr/io.h>
#include "Uart_driver.h"
#include <util/delay.h>
#include <avr/interrupt.h>


void interrupt_init(){

    DDRE &= ~(1 << PE0); 

    cli(); // Clear global interrupt flag 

    EMCUCR |= (1 << ISC2); // Rising edge interrupt on int2
    GICR |= (1 << INT2);


    MCUCR |= (1 << ISC11) | (1 << ISC10); // Rising edge interrupt on int0
    GICR |= (1 << INT1);


    sei(); // Set external interrupt. 

    //set_sleep_mode(SLEEP_MODE_PWR_SAVE);

}


ISR(INT2_vect){

    PORTB &= ~(1 << PB0);

}

ISR(INT1_vect){

    PORTB |= (1 << PB0);

}

int main(){
    
    uart_init(9600);
    interrupt_init();


    DDRB = (1 << PB0) | (1 << PB1);

    while(1){
        PORTB ^= (1 << PB1);
        _delay_ms(1000);
    }


    return 0;
}