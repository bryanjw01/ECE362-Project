/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include <stdio.h>
#include "sinewave.h"
void nano_wait(int t);
void init_lcd(void);
void display1(const char *s);
void display2(const char *s);

#define G1 11	// PA11
#define G2 10	// PA 10
#define B1 2	// PD 2
#define B2 3 	// PB 3
#define R1 13 	// PA 13
#define R2 12 	// PA 12

#define A 4 	// PB 4
#define B 5 	// PB 5
#define C 6 	// PB 6
#define D 7		// PB 7

#define LAT 13 	// PB 13
#define OE 11 	// PC 11
#define CLK 12 	// PC 12



#define B0  10256.41/31
#define C1  10256.41/33
#define CS1 10256.41/35
#define _D1  10256.41/37
#define DS1 10256.41/39
#define E1  10256.41/41
#define F1  10256.41/44
#define FS1 10256.41/46
#define G1S  10256.41/49
#define GS1 10256.41/52
#define A1  10256.41/55
#define AS1 10256.41/58
#define B1S  10256.41/62
#define C2  10256.41/65
#define CS2 10256.41/69
#define _D2  10256.41/73
#define DS2 10256.41/78
#define E2  10256.41/82
#define F2  10256.41/87
#define FS2 10256.41/93
#define G2S  10256.41/98
#define GS2 10256.41/104
#define A2  10256.41/110
#define AS2 10256.41/117
#define B2S  10256.41/123
#define C3  10256.41/131
#define CS3 10256.41/139
#define _D3  10256.41/147
#define DS3 10256.41/156
#define E3  10256.41/165
#define F3  10256.41/175
#define FS3 10256.41/185
#define G3  10256.41/196
#define GS3 10256.41/208
#define A3  10256.41/220
#define AS3 10256.41/233
#define B3  10256.41/247
#define C4  10256.41/262
#define CS4 10256.41/277
#define D4  10256.41/294
#define DS4 10256.41/311
#define E4  10256.41/330
#define F4  10256.41/349
#define FS4 10256.41/370
#define G4  10256.41/392
#define GS4 10256.41/415
#define A4  10256.41/440
#define AS4 10256.41/466
#define B4  10256.41/494
#define C5  10256.41/523
#define CS5 10256.41/554
#define D5  10256.41/587
#define DS5 10256.41/622
#define E5  10256.41/659
#define F5  10256.41/698
#define FS5 10256.41/740
#define G5  10256.41/784
#define GS5 10256.41/831
#define A5  10256.41/880
#define AS5 10256.41/932
#define B5  10256.41/988
#define C6  10256.41/1047
#define CS6 10256.41/1109
#define D6  10256.41/1175
#define DS6 10256.41/1245
#define E6  10256.41/1319
#define F6  10256.41/1397
#define FS6 10256.41/1480
#define G6  10256.41/1568
#define GS6 10256.41/1661
#define A6  10256.41/1760
#define AS6 10256.41/1865
#define B6  10256.41/1976
#define C7  10256.41/2093
#define CS7 10256.41/2217
#define D7  10256.41/2349
#define DS7 10256.41/2489
#define E7  10256.41/2637
#define F7  10256.41/2794
#define FS7 10256.41/2960
#define G7  10256.41/3136
#define GS7 10256.41/3322
#define A7  10256.41/3520
#define AS7 10256.41/3729
#define B7  10256.41/3951
#define C8  10256.41/4186
#define CS8 10256.41/4435
#define D8  10256.41/4699
#define DS8 10256.41/4978
#define out 13333

#define T025 (203.125/4)*3
#define T05 (203.125/2)*3
#define T1 203.125*3
#define T2 406.250*3
#define T3 609.375*3
#define T4 812.500*3
#define T5 1015.625*3
#define T6 1218.750*3
typedef struct {
  uint8_t x1;
  uint8_t y1;
} point;
point nodes[63*15];
int num_nodes=0;
int score=0;
uint8_t snake[64][16];
const uint8_t SNEK[]={

0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,
0,0,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,
0,0,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,
0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,
0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,1,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,
0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,
0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};
uint8_t game_over[]={
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,0,1,1,1,1,1,1,0,1,1,0,0,0,0,1,1,0,1,1,0,0,1,1,0,0,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
uint8_t game_over1[]={
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
const double frequencies[]={
		E5,B4,C5,D5,C5,B4,A4,A4,
		C5,E5,D5,C5,B4,B4,C5,D5,
		E5,C5,A4,A4,out,
		D5,F5,A5,G5,F5,E5,C5,E5,
		D5,C5,B4,B4,C5,D5,E5,C5,
		A4,A4,out,

		E5,B4,C5,D5,C5,B4,A4,A4,
		C5,E5,D5,C5,B4,B4,C5,D5,
		E5,C5,A4,A4,out,
		D5,F5,A5,G5,F5,E5,C5,E5,
		D5,C5,B4,B4,C5,D5,E5,C5,
		A4,A4,out,

		E4,C4,D4,B3,C4,A3,GS3,B3,
		E4,C4,D4,B3,C4,E4,A4,A4,GS4,out,

		        ///////MARIO///////
		        E4,E4,out,E4,
		        out,C4,E4,out,
		        G4,out,out,out,
		        G3,out,out,out,

		        C4,out,out,G3,
		        out,out,E4,out,
		        out,A3,out,B3,
		        out,AS3,A3,out,

		        G3,E4,G4,
		        A4,out,F4,G4,
		        out,E4,out,C4,
		        D4,B3,out,out,

		        C4,out,out,G3,
		        out,out,E3,out,
		        out,A3,out,B3,
		        out,AS3,A3,out,

		        G3,E4,G4,
		        A4,out,F4,G4,
		        out,E4,out,C4,
		        D4,B3,out,out,

};
const double duration[]={
        ///////TETRIS///////
T2,T1,T1,T2,T1,T1,T2,T1,
T1,T2,T1,T1,T2,T1,T1,T2,
T2,T2,T2,T2,T1,
T3,T1,T2,T1,T1,T3,T1,T2,
T1,T1,T2,T1,T1,T2,T2,T2,
T2,T2,T1,

T2,T1,T1,T2,T1,T1,T2,T1,
T1,T2,T1,T1,T2,T1,T1,T2,
T2,T2,T2,T2,T1,
T3,T1,T2,T1,T1,T3,T1,T2,
T1,T1,T2,T1,T1,T2,T2,T2,
T2,T2,T1,

T4,T4,T4,T4,T4,T4,T4,T4,
T4,T4,T4,T4,T2,T2,T2,T2,T6,T1,

        ///////MARIO///////
        T1,T1,T1,T1,
        T1,T1,T1,T1,
        T1,T1,T1,T1,
        T1,T1,T1,T1,

        T1,T1,T1,T1,
        T1,T1,T1,T1,
        T1,T1,T1,T1,
        T1,T1,T1,T1,

        T2,T2,T2,
        T1,T1,T1,T1,
        T1,T1,T1,T1,
        T1,T1,T1,T1,

        T1,T1,T1,T1,
        T1,T1,T1,T1,
        T1,T1,T1,T1,
        T1,T1,T1,T1,

        T2,T2,T2,
        T1,T1,T1,T1,
        T1,T1,T1,T1,
        T1,T1,T1,T1,


};

int apple[]={60,5,45,2,61,8,61,20,11,97,23,49,23,34,1,20,60,15,5,50};

int x=31;
int y=7;
int dx=0;
int dy=0;
int total_apple=20;
int num_apple=0;
void dac_init(void) {
	RCC->AHBENR|=RCC_AHBENR_GPIOAEN;
	GPIOA->MODER&=~(3<<(2*4));
	GPIOA->MODER|=(3<<(2*4));
	RCC->APB1ENR|=RCC_APB1ENR_DACEN;

	DAC->CR&=DAC_CR_EN1;
	DAC->CR&=~DAC_CR_BOFF1;
	DAC->CR|=DAC_CR_TEN1;
	DAC->CR|=DAC_CR_DMAEN1;
	DAC->CR|=DAC_CR_EN1;
}

int h=0;
void tim6_init(void) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	TIM6->PSC =13-1;
	TIM6->ARR =frequencies[h];
	TIM6->CR2|=TIM_CR2_MMS_1;
	TIM6->CR1=TIM_CR1_ARPE;
	TIM6->CR1|=TIM_CR1_CKD_0;
	TIM6->CR1 |= TIM_CR1_CEN;
}


void dma3_init(void) {
	RCC->AHBENR|=RCC_AHBENR_DMA1EN;
	DMA1_Channel3->CMAR=(uint32_t)sine_table;
	DMA1_Channel3->CPAR=(uint32_t) (&(DAC->DHR12R1));
	DMA1_Channel3->CNDTR=sizeof(sine_table)/2;
	DMA1_Channel3->CCR|=DMA_CCR_DIR;
	DMA1_Channel3->CCR|=DMA_CCR_CIRC;
	DMA1_Channel3->CCR|=DMA_CCR_MINC;
	DMA1_Channel3->CCR&=~DMA_CCR_PINC;
	DMA1_Channel3->CCR|=DMA_CCR_MSIZE_0;
	DMA1_Channel3->CCR|=DMA_CCR_PSIZE_0;
	DMA1_Channel3->CCR&=~DMA_CCR_PL;
	DMA1_Channel3->CCR|=DMA_CCR_EN;
}



int k=0;
void TIM3_IRQHandler(void) {
	if((TIM3->SR & TIM_SR_UIF) != 0){
		TIM3->SR &= ~TIM_SR_UIF;
	}

	if(h==sizeof(frequencies)/8){
		h=0;
	}
	if(k==sizeof(duration)/8-1){
		k=0;
	}
	k++;
	TIM3->PSC=duration[k];
	TIM6->ARR=frequencies[h];
	h++;
}




void tim3_init(void) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->PSC =duration[k] - 1;
	TIM3->ARR =1000000-1;
	TIM3->DIER |=TIM_DIER_UIE;
	TIM3->CR1 |= TIM_CR1_CEN;
	NVIC->ISER[0]=1<<TIM3_IRQn;
}

void init_snake(void){
	for(int i=0;i<16;i++){
		for(int j=0;j<64;j++){
			snake[j][i]=0;
		}
	}
}
void move_snake(void){
	char line[21];
	snake[nodes[num_nodes].x1+dx][nodes[num_nodes].y1+dy]=1;

	for(int i=0;i<=num_nodes+1;i++){
		if(i==num_nodes+1){
			if(nodes[num_nodes].x1+dx==(apple[num_apple]%64)&&nodes[num_nodes].y1+dy==(apple[num_apple]%16)){
				if(TIM2->ARR!=50){
					TIM2->ARR-=10;
				}
				num_nodes++;
				num_apple++;
				if(num_apple==16){
					num_apple=0;
				}
				nodes[num_nodes].x1=nodes[num_nodes-1].x1+dx;
				nodes[num_nodes].y1=nodes[num_nodes-1].y1+dy;
				score+=10;
				sprintf(line, "Score: %d",score);
				display1(line);

				return;
			}
		}
		else if(x==nodes[i].x1&&y==nodes[i].y1&&(dx!=0||dy!=0)){
			game_over2();
		}
		if(nodes[i].x1==apple[num_apple]%64&&nodes[num_nodes].y1==apple[num_apple]%16){
			if(TIM2->ARR!=50){
			TIM2->ARR-=10;
			}
			num_nodes++;
			num_apple++;
			if(num_apple==16){
				num_apple=0;
			}
			nodes[num_nodes].x1=nodes[num_nodes-1].x1+dx;
			nodes[num_nodes].y1=nodes[num_nodes-1].y1+dy;
			score+=10;
			sprintf(line, "Score: %d",score);
			display1(line);
			return;
		}

	}

	snake[nodes[0].x1][nodes[0].y1]=0;
	for(int i=0;i<num_nodes;i++){
		nodes[i].x1=nodes[i+1].x1;
		nodes[i].y1=nodes[i+1].y1;
	}
	nodes[num_nodes].x1+=dx;
	nodes[num_nodes].y1+=dy;

}
void init_joystick(void){
	char line[20];
	init_lcd();
		RCC-> AHBENR |= RCC_AHBENR_GPIOBEN;
		GPIOB->MODER |=0xf;
		RCC->APB2ENR |=RCC_APB2ENR_ADC1EN;
		RCC->CR2 |= RCC_CR2_HSI14ON;
		while (!( RCC->CR2 & RCC_CR2_HSI14RDY));
			ADC1->CR |= ADC_CR_ADEN;
		while (!(ADC1->ISR & ADC_ISR_ADRDY));
		while ((ADC1-> CR & ADC_CR_ADSTART));
}
void joystick(void){

						ADC1->CHSELR= 0;
						ADC1 -> CHSELR |= 1<<8;
						while(!(ADC1->ISR & ADC_ISR_ADRDY));
						ADC1-> CR |= ADC_CR_ADSTART;
						while (!(ADC1 ->ISR & ADC_ISR_EOC));

						if(ADC1->DR * 3/4095.0>2&&dx==0){
							dx=1;
							dy=0;
						}
						else if(ADC1->DR*3/4095.0<1&&dx==0){
							dx=-1;
							dy=0;
						}
						ADC1->CHSELR = 0;
						ADC1->CHSELR |= 1<<9;
						while(!(ADC1 -> ISR & ADC_ISR_ADRDY));
						ADC1 -> CR |= ADC_CR_ADSTART;
						while(!(ADC1->ISR & ADC_ISR_EOC ));
						if(ADC1->DR * 3/4095.0>2&&dy==0){
							dx=0;
							dy=-1;
						}
						else if(ADC1->DR*3/4095.0<1&&dy==0){
							dx=0;
							dy=1;
						}

}
void game_over2(){
	NVIC->ICER[0]|=1<<TIM2_IRQn;
	NVIC->ICER[0]|=1<<TIM3_IRQn;
	TIM6->ARR=0;
	int i=0;
	while(1){

		for(int j=0;j<64;j++){
					if(i==0||j==0||(j==63)||i==15){
						GPIOD->ODR|=1<<B1;
					}
					else if(game_over[(j+i*64)]==1){
						GPIOA->ODR|=1<<B1;
						GPIOA->ODR&=~1<<R1;
						GPIOA->ODR=1<<G1;
					}
					else{
						GPIOA->ODR&=~1<<B1;
						GPIOA->ODR&=~1<<G1;
						GPIOD->ODR&=~1<<B1;
						GPIOA->ODR&=~1<<R1;
						GPIOB->ODR&=~1<<B2;
					}
					if(i==0||j==0||(j==63)||i==15){
						GPIOA->ODR|=1<<G2;
					}
					else if(game_over1[(j+i*64)]==1){
						GPIOB->ODR|=1<<B2;
					}
					else{
						//GPIOA->ODR|=1<<G2;
						GPIOB->ODR&=~1<<B2;
						//GPIOA->ODR|=1<<R2;
					}
				GPIOC->ODR|= 1<<CLK;
				GPIOC->ODR &=~(1<<CLK);
		}
	GPIOC->ODR|=1<<OE;
		GPIOB->ODR|=1<<LAT;
		GPIOB->ODR &= ~(1<<LAT);
		GPIOC->ODR &= ~(1<<OE);
		GPIOB->ODR &= ~(0xf<<4);
		GPIOB->ODR|= (i<<4);
		i++;
		if(i==16){
			i=0;
		}
		//joystick();
	}
}
void TIM2_IRQHandler(void){

	TIM2->SR&=~TIM_SR_UIF;
	x+=dx;
	y+=dy;
	if(x==63){
		game_over2();
	}
	if(x==0){
		game_over2();
	}
	if(y==15){
		game_over2();
	}
	if(y==0){
		game_over2();
	}
	move_snake();

}

void init_tim2(void){

	RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;
	TIM2->PSC=48000-1;
	TIM2->ARR=150-1;
	TIM2->DIER|=TIM_DIER_UIE;
	TIM2->CR1|=TIM_CR1_CEN;
	NVIC->ISER[0]|=1<<TIM2_IRQn;
}


void init_GPIOx(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~(GPIO_MODER_MODER10 | GPIO_MODER_MODER11 | GPIO_MODER_MODER12 | GPIO_MODER_MODER13);
	GPIOA->MODER |= GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0 | GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0;
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	GPIOB->MODER &= ~(GPIO_MODER_MODER3 | GPIO_MODER_MODER4| GPIO_MODER_MODER5 |GPIO_MODER_MODER6| GPIO_MODER_MODER7 | GPIO_MODER_MODER13);
	GPIOB->MODER |= GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0| GPIO_MODER_MODER5_0 |GPIO_MODER_MODER6_0| GPIO_MODER_MODER7_0 |GPIO_MODER_MODER13_0;
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC->MODER &= ~(GPIO_MODER_MODER11 | GPIO_MODER_MODER12);
	GPIOC->MODER |= GPIO_MODER_MODER11_0 | GPIO_MODER_MODER12_0;
	RCC->AHBENR |= RCC_AHBENR_GPIODEN;
	GPIOD->MODER &= ~(GPIO_MODER_MODER2);
	GPIOD->MODER |= GPIO_MODER_MODER2_0;
}
void init_LED_Matrix(void){
//	char line[20];
//	sprintf(line, "Score: 0");
//		display1(line);
		//y=1;
			int i=0;
			GPIOB->ODR&=~(0xf<<4);
		snake[x][y+1]=1;
		nodes[0].x1=x;
		nodes[0].y1=y+1;
		snake[x][y]=1;
		nodes[1].x1=x;
		nodes[1].y1=y;
		num_nodes=1;
	while(1){

		for(int j=0;j<64;j++){
					if(i==0||j==0||(j==63)||i==15){
						GPIOD->ODR|=1<<B1;
					}
					else if(snake[j][i]>0){
						GPIOA->ODR|=1<<B1;
						GPIOA->ODR&=~1<<R1;
						GPIOA->ODR=1<<G1;
					}
					else if(apple[num_apple]%64==j&&apple[num_apple]%16==i){
						GPIOA->ODR|=1<<R1;
					}
					else{
						GPIOA->ODR&=~1<<B1;
						GPIOA->ODR&=~1<<G1;
						GPIOD->ODR&=~1<<B1;
						GPIOA->ODR&=~1<<R1;
						GPIOB->ODR&=~1<<B2;
					}
					if(SNEK[(j+i*64)]==1){
						GPIOA->ODR|=1<<R2;
					}
					else{
						GPIOA->ODR|=1<<G2;
						GPIOB->ODR|=1<<B2;
						GPIOA->ODR|=1<<R2;
					}
				GPIOC->ODR|= 1<<CLK;
				GPIOC->ODR &=~(1<<CLK);
		}
	GPIOC->ODR|=1<<OE;
		GPIOB->ODR|=1<<LAT;
		GPIOB->ODR &= ~(1<<LAT);
		GPIOC->ODR &= ~(1<<OE);
		GPIOB->ODR &= ~(0xf<<4);
		GPIOB->ODR|= (i<<4);
		i++;
		if(i==16){
			i=0;
		}
		joystick();
	}

}

int main(void){
	dac_init();
	tim6_init();
	dma3_init();
	tim3_init();
	init_snake();
	init_tim2();
	init_GPIOx();
	init_joystick();
	init_LED_Matrix();
	while(1){

	}
	return 0;
}
