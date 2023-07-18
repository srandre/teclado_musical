#include "lcd_controller.h"
#include "general_controller.h"
#include "audio_controller.h"

int main(void) {
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; //Enable AFIO
	AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE; //Disable JTAG
	
	initializeGPIOs();
	initializePWM();
	initializeADC();
	delay_ms(1);
	
	printHUD();
	
	while(1){
		clearOutput();
		
		handleGPIO_A(GPIOA->IDR);
		handleGPIO_B(GPIOB->IDR);
		handleGPIO_C(GPIOC->IDR);
	}
}