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

#include <src/icons.h>
#include <src/asmroutines.c>

#define SCREEN_WIDTH 96
#define SCREEN_HEIGHT 64

#define KEY_UP 4
#define KEY_DOWN 1
#define KEY_LEFT 2
#define KEY_RIGHT 3
#define KEY_QUIT 9
#define KEY_SHOOT 69

uint8_t px,py,dx,dy;

uint8_t temps[6];

char *hudthing;

uint8_t lerp(a,b,t){return (1-t)*a+t*b;}

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
	csleep(50);
	putsprite(SPR_AND,9,20,spr_logo);
	for(uint8_t i=0;i<10;i++)
	{
		changeLCDz(i);
		csleep(10);
	}
	changeLCDz(0);
	csleep(100);
	putsprite(spr_or,76,31,spr_ti);
	putsprite(spr_mask,76,31,spr_timask);
	temps[0]=true;
	csleep(100);
	while(temps[0])
	{
		switch(getCSC())
		{
			case KEY_QUIT:
				exit(0);
				break;
			case KEY_SHOOT:
				temps[0]=false;
				break;
		}
	}

	csleep(250);
	temps[0]=true;
	clg();
	while (true)
	{
		//TODO : find out the keycodes of the buttons
		switch(getCSC())
		{
			case KEY_SHOOT:
				exit(0);
				break;
			case KEY_UP:
				dy--;
				break;
			case KEY_DOWN:
				dy++;
				break;
			case KEY_RIGHT:
				dx++;
				break;
			case KEY_LEFT:
				dx--;
				break;
		}
		py=py+dy;
		px=px+dx;
		unplot(px+dx,py+dy);
		dx,dy=0;
		plot(px,py);
	}
	
	return 0;
}
