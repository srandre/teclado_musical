#ifndef GENERAL_CONTROLLER_H
#define GENERAL_CONTROLLER_H
#include "audio_controller.h"
#include "lcd_controller.h"

void initializeGPIOs(void);
void initializeADC(void);
void handleGPIO_A(uint16_t key);
void handleGPIO_B(uint16_t key);
void handleGPIO_C(uint16_t key);
void clearOutput(void);
void initializePWM(void);

//Turns off LEDs, buzzer, etc
void clearOutput(void) {
	GPIOA->ODR = 0x0000;
	GPIOB->ODR = 0x0000;
	TIM3->CCR3 = 0;
}

//Initializes PWM signal for buzzer
void initializePWM(void) {
	RCC->APB1ENR |= (1<<1); 		//Enable TIM3 clock
	TIM3->CCMR2 = 0x0068; 			//PWM1 mode
	TIM3->CCER = 0x0100; 				//Habilita buffer saída + captura borda subida
	TIM3->ARR = SET_ARR;
	TIM3->CCR3 = 0; 						//Starts off duty cycle
	TIM3->CR1 = 1; 							//ENABLE timer
}

//Initializes ADC1 for potentiometer
void initializeADC(void) {
	RCC->APB2ENR |= (1<<9) | (1<<14); //Enables clocks for ADC1 and usart1
	ADC1->CR2 = 1; //Set ADON (power up)
	ADC1->SMPR2 = 1<<27; //Set SMP1 (001)m, channel 9
	delay_us(1);
}

void initializeGPIOs(void) {
	RCC->APB2ENR |= 0xFC; //Enable clocks for GPIOs
	
	GPIOA->CRL = 0x43344333; 		// PA03, PA04, PA07 as regular inputs, rest as outputs
	GPIOA->CRH = 0x33333333; 		// PA08 - PA15 as outputs
	
	GPIOB->CRL = 0x4444440B; 		// PB01 as analog input, PB02 - PB07 as inputs, alternating function for PB00
	GPIOB->CRH = 0x44444444; 		// PB08 - PB15 as inputs
	
	GPIOC->CRL = 0x44444444; 		// PC00 - PC07 as inputs
	GPIOC->CRH = 0x44444444; 		// PC08 - PC15 as inputs
}

void handleGPIO_A(uint16_t key) {
	switch(key) {
			case 0x2018: //SW14 -> PA7 -> D#
				play(currentOctave, Dsharp, 10);
				break;
			case 0x2090: //SW8 -> PA3 -> F
				play(currentOctave, F, 10);
				break;
			case 0x2088: //SW9 -> PA4 -> G
				play(currentOctave, G, 10);
				break;
			default:
					clearOutput();
				break;
		}
}

void handleGPIO_B(uint16_t key) {
	switch(key) {
			case 0xEFF8: //SW1 -> PB12 -> Switch to next octave
				if(currentOctave == 7) {
					currentOctave = 1;
				} else {
					currentOctave++;
				}
				printHUD();
				delay_ms(100);
				break;
			case 0xDFF8: //SW2 -> PB13 -> Switch to previous octave
				if(currentOctave == 1) {
					currentOctave = 7;
				} else {
					currentOctave--;
				}
				printHUD();
				delay_ms(100);
				break;
			case 0xBFF8: //SW3 -> PB14 -> Switch to next duty cycle
				switch(currentCycle) {
					case 25:
						currentCycle = 50;
						break;
					case 50:
						currentCycle = 75;
						break;
					case 75:
						currentCycle = 25;
						break;
				}
				printHUD();
				delay_ms(100);
				break;
			case 0x7FF8: { //SW4 -> PB15 -> Play random song
				switch(currentSong) {
					case 1:
						playStarWars();
						break;
					case 2:
						playIndianaJones();
						break;
					case 3:
						playRickAstley();
						break;
					case 4:
						playJojo();
						break;
					default:
						break;
				}
				//Cycles to next song
				if(currentSong == 4) {
					currentSong = 1;
				} else {
					currentSong++;
				}
				break;
			}
			case 0xFFD8: //SW5 -> PB5 -> C
				play(currentOctave, C, 10);
				break;
			case 0xFBF8: //SW13 -> PB10 -> C#
				play(currentOctave, Csharp, 10);
				break;
			case 0xFFE8: //SW6 -> PB4 -> D
				play(currentOctave, D, 10);
				break;
			case 0xFFF0: //SW7 -> PB3 -> E
				play(currentOctave, E, 10);
				break;
			case 0xFEF8: //SW10 -> PB8 -> A
				play(currentOctave, A, 10);
				break;
			case 0xFDF8: //SW11 -> PB9 -> B
				play(currentOctave, B, 10);
				break;
			case 0xF7F8: //SW12 -> PB11 -> C
				play(currentOctave + 1, C, 10);
				break;
			default:
				clearOutput();
				break;
		}
}

void handleGPIO_C(uint16_t key) {
	switch(key) {
			case 0x6000: //SW15 -> PC15 -> F#
				play(currentOctave, Fsharp, 10);
				break;
			case 0xA000: //SW16 -> PC14 -> G#
				play(currentOctave, Gsharp, 10);
				break;
			case 0xC000: //SW17 -> PC13 -> A#
				play(currentOctave, Asharp, 10);
				break;
			default:
				clearOutput();
				break;
		}
}

#endif