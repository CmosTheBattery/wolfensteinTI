#pragma data icon 0xEB,0x6B,0x6B,0x6B,0x6B,0x6B,0x7E,0x6C;
#pragma data mirage_icon 0x02,0x22,0x82,0x22,0xc2,0x22,0xE2,0x22,0xE2,0x22,0xE2,0x22,0xE2,0x22,0xE2,0x22,0xE2,0x22,0xE0,0x02,0xE0,0x02,0xE0,0x02,0xE0,0x0E,0xE2,0x3E,0xE6,0x7E;
#pragma string name WOLFENSTEIN TI
#pragma output nostreams

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>

#include <graphics.h>
#include <games.h>

#include <icons.h>

#define SCREEN_WIDTH 96
#define SCREEN_HEIGHT 64

#define KEY_UP 4
#define KEY_DOWN 1
#define KEY_LEFT 2
#define KEY_RIGHT 3
#define KEY_QUIT 9
#define KEY_SHOOT 69

int flag=1;
bool exita=true;
int tick=0;

int px,py;

int temps[6];

char *hudthing;

int lerp(a,b,t){return (1-t)*a+t*b;}

void draw_player()
{
	plot(px,py);
}

void clgblack()
{
	//HACK : yeahh
	putsprite(SPR_OR,0,0,spr_black);
	//inline asm always gets the job done Oᴗ-
	//and can soft lock the calculator O_O
	/*
	TODO : this shit doesn't work
	__asm
		push af
		push bc
		ld a,$01		   ; 8-bit mode
		out ($10),a
		call $000B
	
		ld a,$40		   ; Set Z
		out ($10),a
		call $000B

		ld a,$20		   ; Set Column
		out ($10),a
		call $000B

		ld a,$80		   ; Set Row
		out ($10),a
		call $000B

		ld c,$0B		   ; Y loop counter (rows)
	loopy:
		ld a,c
		add a,$20		; Set column for this row
		out ($10),a
		call $000B

		ld a,$80		   ; Row start
		out ($10),a
		call $000B

		ld b,$3F		   ; X loop counter (columns)
		ld a,$FF		   ; B L A C K
	loopx:
		out ($11),a
		call $000B
		djnz loopx

		dec c
		jp p,loopy
		
		pop bc
		pop af
		ret
	__endasm
	*/
}

static uint8_t getCSC(void) __naked {
	__asm
		rst  0x28 ; bcall dispatcher
		defw 0x4018 ; _GetCSC
		ld   l,a ; return value -> HL
		ld   h,0
		ret
	__endasm;
}

void handle_input()
{
	//TODO : find out the keycodes of the buttons
	switch(getCSC())
	{
		case KEY_SHOOT:
			exita=false;
			break;
		case KEY_UP:
			py--;
			break;
		case KEY_DOWN:
			py++;
			break;
		case KEY_RIGHT:
			px++;
			break;
		case KEY_LEFT:
			px--;
			break;
	}
}

void draw_hud()
{
	draw(0, 50, 20, 50);
	drawto(22, 52);
	drawto(22, 63);
	putsprite(SPR_OR,1,52,spr_heart);
	putsprite(SPR_OR,1,58,spr_clip);
}

main()
{
	clgblack();
	putsprite(SPR_AND,9,20,spr_logo);
	temps[0]=false;
	csleep(100);
	while(temps[0])
	{
		switch(getCSC())
		{
			case KEY_QUIT:
				exit(0);
				break;
			default:
				temps[0]=true;
				break;
		}
	}
	
	/*
	while(exita)
	{
		tick++;
		switch(flag)
		{
			case 1:
				clgblack();
				putsprite(SPR_AND,9,20,spr_logo);
				if(getk()==11){exit=false;}
				if(getk()==9){flag=2;}
				break;
			case 2:
				clg();
				draw_hud();
				draw_player();
				handle_input();
				break;
		}
	}
	*/
	return 0;
}
