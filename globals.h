#ifndef GLOBALS_H
#define GLOBALS_H

enum notes {
	C = 1,
	Csharp = 2,
	D = 3,
	Dsharp = 4,
	E = 5,
	F = 6,
  Fsharp = 7,
	G = 8,
	Gsharp = 9,
	A = 10,
	Asharp = 11,
	B = 12
};

//Context variables
int currentOctave = 4;
int currentCycle = 75;
int playList[] = {1, 2, 3, 4};
int currentSong = 1;
double currentFrequencyMultiplier = 1;

//Constants
#define SET_ARR 999
#define POT_HIGH_VALUE 0x0F00
#define MAX_FREQUENCY_MULTIPLIER 2

#define LCD_RS 15 // PA15
#define LCD_EN 12 // PA12
#define LCD4 8    // PA08
#define LCD5 6    // PA06
#define LCD6 5    // PA05
#define LCD7 11   // PA11

#define SW1 12 		// PB12
#define SW2 13 		// PB13
#define SW3 14 		// PB14
#define SW4 15 		// PB15
#define SW5 5			// PB05
#define SW6 4			// PB04
#define SW7 3 		// PB03
#define SW8 3 		// PA03
#define SW9 4 		// PA04
#define SW10 8 		// PB08
#define SW11 9 		// PB09
#define SW12 11 	// PB11
#define SW13 10 	// PB10
#define SW14 7 		// PA07
#define SW15 15 	// PC15
#define SW16 14 	// PC14
#define SW17 13		// PC13

#define LED1 0		// PA00
#define LED2 1 		// PA01
#define LED3 2		// PA02
#define LED4 15		// PA15
#define LED5 8		// PA08
#define LED6 6		// PA06
#define LED7 5 		// PA05
#define LED8 11 	// PA11

#define BZ 0 			// PA00

#endif