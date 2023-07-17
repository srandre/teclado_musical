#ifndef AUDIO_CONTROLLER_H
#define AUDIO_CONTROLLER_H
#include <stm32f10x.h>
#include "globals.h"

void handleAnal_Input(void);
void delay_us ( uint16_t t);
void delay_ms ( uint16_t t);
double getPSC (int octave, enum notes note);
void play (int octave, enum notes note, uint16_t duration_ms);
void playStarWars(void);
void playRickAstley(void);
void playIndianaJones(void);
void playJojo(void);

void handleAnal_Input(void) {
	ADC1->SQR3 = 9; //Channel 1 as input
	ADC1->CR2 = 1; //ADCON = 1
	double adcValue = ADC1->DR;
	
	//Frequency multiplier is a number from
	//1 to MAX_FREQUENCY_MULTIPLIER, proportional
	//to the increase of the POT knob output
	currentFrequencyMultiplier = 1 + (adcValue*MAX_FREQUENCY_MULTIPLIER)/POT_HIGH_VALUE;
}

void delay_us ( uint16_t t){
	volatile unsigned long l = 0;
	uint16_t i;
	for(i = 0; i < t; i++) {
		for (l = 0; l < 6; l++){}
	}
}

void delay_ms ( uint16_t t ) {
	volatile unsigned long l = 0;
	uint16_t i;
	for (i = 0; i < t; i++) {
		for (l = 0; l < 6000; l++){}
	}
 }

//Returns PSC value for playing a specific note in a specific octave
double getPSC ( int octave, enum notes note ) {
	double notesFirstOctave[] = { 32.7032, 34.64783, 36.7081, 38.89087, 41.20344, 43.65363, 46.2493, 48.99943, 51.91309, 55, 58.27047, 61.73541 };
	double baseNote = notesFirstOctave[note - 1];
	double octaveMultiplier = 1 << octave;
	
	double noteFrequency = baseNote * octaveMultiplier * currentFrequencyMultiplier;
	
	double psc = (SystemCoreClock/((SET_ARR + 1) * noteFrequency)) - 1;
	return psc;
}

//Plays 'note' in 'octave' for 'duration_ms' milisseconds,
//while checking for musical bends every 'step' milisseconds.
void play (int octave, enum notes note, uint16_t duration_ms) {
	int i;
	int step = 10;
	for (i = 0; i < duration_ms; i += step) {
		handleAnal_Input();
		
		TIM3->PSC = getPSC(octave, note);
		TIM3->CCR3 = currentCycle;
		delay_ms(step);
		TIM3->CCR3 = 0;
	}
}

void playStarWars(void) {
	play(currentOctave, C, 500);
	play(currentOctave, G, 500);
	play(currentOctave, F, 80);
	play(currentOctave, E, 80);
	play(currentOctave, D, 70);
	play(currentOctave + 1, C, 500);
	play(currentOctave, G, 250);
	play(currentOctave, F, 80);
	play(currentOctave, E, 80);
	play(currentOctave, D, 70);
	play(currentOctave + 1, C, 500);
	play(currentOctave, G, 250);
	play(currentOctave, F, 80);
	play(currentOctave, E, 80);
	play(currentOctave, F, 70);
	play(currentOctave, D, 500);
}
void playRickAstley(void) {
	play(currentOctave, G, 80);
	play(currentOctave, A, 80);
	play(currentOctave + 1, C, 100);
	play(currentOctave, A, 100);
	play(currentOctave + 1, E, 200);
	delay_ms(50);
	play(currentOctave + 1, E, 180);
	play(currentOctave + 1, D, 400);
	delay_ms(50);
	
	play(currentOctave, G, 80);
	play(currentOctave, A, 80);
	play(currentOctave + 1, C, 100);
	play(currentOctave, A, 100);
	play(currentOctave + 1, D, 200);
	delay_ms(50);
	play(currentOctave + 1, D, 180);
	play(currentOctave + 1, C, 400);
	delay_ms(50);
	
	play(currentOctave, G, 80);
	play(currentOctave, A, 80);
	play(currentOctave + 1, C, 100);
	play(currentOctave, A, 100);
	play(currentOctave + 1, C, 200);
	delay_ms(50);
	play(currentOctave + 1, D, 180);
	delay_ms(50);
	play(currentOctave, B, 200);
	delay_ms(50);
	play(currentOctave, A, 150);
	play(currentOctave, G, 80);
	
	delay_ms(50);
	play(currentOctave, G, 200);
	play(currentOctave + 1, D, 300);
	play(currentOctave + 1, C, 400);
}
void playIndianaJones(void) {
	//FIRST BAR
	play(currentOctave, Fsharp, 200);
	play(currentOctave, G, 80);
	
	//SECOND BAR
	play(currentOctave, A, 150);
	play(currentOctave + 1, D, 400);
	delay_ms(100);
	play(currentOctave, E, 200);
	play(currentOctave, Fsharp, 80);
	
	//THIRD BAR
	play(currentOctave, G, 400);
	delay_ms(100);
	play(currentOctave, A, 200);
	play(currentOctave, B, 80);
	
	//FOURTH BAR
	play(currentOctave + 1, Csharp, 150);
	play(currentOctave + 1, G, 400);
	delay_ms(100);
	play(currentOctave, B, 200);
	play(currentOctave + 1, Csharp, 80);
	
	//FIFTH BAR
	play(currentOctave + 1, D, 250);
	play(currentOctave + 1, E, 250);
	play(currentOctave + 1, Fsharp, 250);
}
void playJojo(void) {
	//FIRST BAR
	play(currentOctave - 1, B, 70);
	delay_ms(70);
	play(currentOctave - 1, B, 70);
	delay_ms(70);
	play(currentOctave - 1, B, 70);
	play(currentOctave - 1, A, 70);
	delay_ms(70);
	play(currentOctave - 1, B, 70);
	delay_ms(70);
	play(currentOctave, D, 70);
	delay_ms(70);
	play(currentOctave - 1, B, 70);
	delay_ms(70);
	play(currentOctave - 1, Fsharp, 70);
	play(currentOctave - 1, A, 70);
	delay_ms(70);
	
	//SECOND BAR
	play(currentOctave - 1, B, 70);
	delay_ms(70);
	play(currentOctave - 1, B, 70);
	delay_ms(70);
	play(currentOctave - 1, B, 70);
	play(currentOctave - 1, A, 70);
	delay_ms(70);
	play(currentOctave - 1, B, 70);
	delay_ms(70);
	play(currentOctave, F, 70);
	delay_ms(70);
	play(currentOctave, E, 70);
	delay_ms(70);
	play(currentOctave, D, 70);
	play(currentOctave - 1, A, 70);
}
#endif