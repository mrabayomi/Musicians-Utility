#include <p18f46K20.h>


#pragma config IESO=OFF, FCMEN=OFF, FOSC=INTIO67, PWRT=OFF, BOREN=OFF, WDTEN=OFF
#pragma config WDTPS=32768, MCLRE=ON, LPT1OSC=OFF, PBADEN=OFF, CCP2MX=PORTBE
#pragma config STVREN=OFF, LVP=OFF, XINST=OFF, DEBUG=OFF, CP0=OFF, CP1=OFF
#pragma config CP2=OFF, CP3=OFF, CPB=OFF, CPD=OFF, WRT0=OFF, WRT1=OFF
#pragma config WRT2=OFF, WRT3=OFF, WRTB=OFF, WRTC=OFF, WRTD=OFF, EBTR0=OFF
#pragma config EBTR1=OFF, EBTR2=OFF, EBTR3=OFF, EBTRB=OFF


// Various includes for the display driver - not that these are MODIFIED from the originals
//#include <stdio.h>

//#include "delays.h"
#include "oled_interface.h"
#include "oled_jib.h" 
#include "oled_cmd.h"

// This allows us to define strings which are held in ROM (of which we have considerable more than RAM). The text cannot be changed but where this is OK this is effieicent use of resourcses
rom const unsigned char hello[] = "Hello";
rom const unsigned char world[] = "World";
unsigned int delay;


/** D E C L A R A T I O N S **************************************************/
#define RB0      PORTBbits.RB0
#define RB1      PORTBbits.RB1
#define RB2      PORTBbits.RB2
#define RB3      PORTBbits.RB3

void InitializeSystem(void);


void main(void){

	InitializeSystem();


	delay = 30000;
	while(delay--);


	// These are the functions you need to use to initialise the display
	oled_init();
	oled_clear();
	oled_refresh();


	// This is the demonstration code provided with the board that shows how
	// individual characters can be displayed.
	oled_putc_1x('\n');
	oled_putc_1x('\t');
	oled_putc_1x('\t');

	oled_puts_rom_1x("\n Anirudh and Abayomi");
	oled_puts_rom_1x ("\n\n Final Project");

	oled_refresh();
	
	Delay10KTCYx(1000);
	
	
	oled_clear();
	oled_puts_rom_1x("Metronome\nFunction");
	oled_puts_rom_1x("\t\t\t Tuning\n Utility");
	oled_puts_rom_1x("\n\n\n RTFD");
	oled_puts_rom_1x("\t\t\t Test \nof \nTuning Utility");

	oled_refresh();
	
	
	while (RB0==1 && RB1==1 && RB2==1 && RB3==1)
	{
	if( RB0 ==0)
	{	
		oled_clear();
		oled_puts_rom_1x ("\t\t\t\n\n\n Metronome Function");
		oled_refresh();
		Delay10KTCYx(1000);

		oled_clear();
		oled_puts_rom_1x ("\t\t\t\n\n\n Please select Upper Time Signature Value");
		oled_refresh();
		Delay10KTCYx(1000);
		
	}
	
		if( RB1 == 0)
	{	
		oled_clear();
		oled_puts_rom_1x ("\t\t\t\n\n\nRTFD");
		oled_refresh();
		Delay10KTCYx(2000);
	}
		if( RB2 ==0)
	{	
		oled_clear();
		oled_puts_rom_1x ("\t\t\t\n\n\nTuning Utility");
		oled_refresh();
		Delay10KTCYx(1000);
		oled_clear();
		oled_puts_rom_1x ("\t\t\t\n\nPlease Select Reference Note");
		oled_refresh();
		
	}
		if( RB3 ==0)
	{	
		oled_clear();
		oled_puts_rom_1x ("\t\t\t\n\n\nTest of Tuning Utility");
		oled_refresh();
		Delay10KTCYx(1000);
	}		
	}

}	

// Intialise the system - you should not need to change any code here 
void InitializeSystem(void)			
{

	OSCCON = 0b01110000;
	OSCTUNEbits.PLLEN = 0; 					// turn off the PLL

	// Setup I/O Ports.
	
	TRISA = 0;								// TRISA outputs
	LATA = 0b11110000;						// drive PORTA pins low

	oled_res = 1;							// do not reset LCD yet
	oled_cs = 1;							// do not select the LCD

	TRISB = 0b11001111;

	LATC = 0b00101000;						// Set up port C
	TRISC = 0b00000000;

	TRISD = 0;								// TRISD is LED output
	LATD = 0;								// turn off LEDS

	TRISE = 0b00000111;						// Set tristate on E (may be overridden in ADC_INIT)

	// Setup TMR1
	// Configure Timer 1
	T1CON 	= 0b00001111;
		
	// Setup TMR2
	T2CON = 0b00000100;						// 1:1 prescaler
	PR2 = 0xFF;
	T0CON = 0x80;

	// Configure MSSP for SPI master mode
	SSPCON1 = 0b00110010;					// clock idle high, Clk /64

	SSPSTAT = 0b00000000;

	PIR1bits.TMR1IF = 0; 
	PIE1bits.TMR1IE = 1; 

	INTCONbits.PEIE = 1; 
	INTCONbits.GIE = 0; 

} 



