#include "general_controller.h"
#ifndef LCD_CONTROLLER_H
#define LCD_CONTROLLER_H
#include <stdio.h>

void lcd_init (void); // Iniciar o display corretamente
void lcd_command (unsigned char cmd); // Enviar comandos
void lcd_data (unsigned char data); // Envia dados ( caractere ASCII )
void lcd_print (char * str); // Envia strings
void lcd_putValue (unsigned char value); // Usada internamente

void printHUD(void);

void lcd_putValue ( unsigned char value ) {
	uint16_t aux ; /* variable to help to build appropriate data out */
	aux = 0x0000 ; /* clear aux */
	GPIOA->BRR = (1 << 5)|(1 << 6)|(1 << 8)|(1 << 11); /* clear data lines */
	aux = value & 0xF0;
	aux = aux >> 4;
	GPIOA->BSRR = (( aux & 0x0008 ) << 8) | (( aux & 0x0004 ) << 3) | (( aux & 0x0002 ) << 5) | (( aux & 0x0001 ) << 8);
	GPIOA->ODR |= (1 << LCD_EN ); /* EN = 1 for H - to - L pulse */
	delay_ms(3); /* make EN pulse wider */
	GPIOA->ODR &= ~ (1 << LCD_EN ); /* EN = 0 for H - to - L pulse */
	delay_ms(1); /* wait */
	GPIOA->BRR = (1 << 5)|(1 << 6)|(1 << 8)|(1 << 11); /* clear data lines */
	aux = 0x0000 ; /* clear aux */
	aux = value & 0x0F;
	GPIOA->BSRR = (( aux & 0x0008 ) << 8) | (( aux & 0x0004 ) << 3) | (( aux & 0x0002 ) << 5) | (( aux & 0x0001 ) << 8);
	GPIOA->ODR |= (1 << LCD_EN ); /* EN = 1 for H - to - L pulse */
	delay_ms (3); /* make EN pulse wider */
	GPIOA->ODR &= ~(1 << LCD_EN ); /* EN = 0 for H - to - L pulse */
	delay_ms (1); /* wait */
}

void lcd_command ( unsigned char cmd ) {
	GPIOA->ODR &= ~ (1 << LCD_RS ); /* RS = 0 for command */
	lcd_putValue ( cmd );
}


void lcd_data ( unsigned char data ) {
	GPIOA->ODR |= (1 << LCD_RS ); /* RS = 1 for data */
	lcd_putValue(data);
}

void lcd_print ( char * str ) {
	unsigned char i = 0;

	while ( str [ i ] != 0) { /* while it is not end of string */
		lcd_data ( str [ i ]); /* show str [ i ] on the LCD */
		i++;
	}
 }

void lcd_init (void) {
	delay_ms (15);
	GPIOA->ODR &= ~(1 << 0 ); /* LCD_EN = 0 */
	delay_ms (3); /* wait 3 ms */
	lcd_command (0x33 ); // lcd init .
	delay_ms (5);
	lcd_command (0x32 ); // lcd init .
	delay_us (3000);
	lcd_command (0x28 ); // 4 - bit mode , 1 line and 5 x8 charactere set
	delay_ms (3);
	lcd_command (0x0e ); // display on , cursor on
	delay_ms (3);
	lcd_command (0x01 ); // display clear
	delay_ms (3);
	lcd_command (0x06 ); // move right
	delay_ms (3);
 }

void printHUD(void) {
	char firstLine[50];
	sprintf(firstLine, "Octave: %d", currentOctave);
	lcd_init();
	lcd_print(firstLine);
	delay_ms(1);
	
	char secondLine[50];
	sprintf(secondLine, "Cycle: %d%%", currentCycle);
	lcd_command(0xC0);
	lcd_print(secondLine);
	delay_ms(1);
}


#endif