#pragma string name KEYTEST

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <graphics.h>
#include <games.h>

#include <src/icons.h>
#include <src/asmroutines.c>

char press[] = "Press a Key...";

int main()
{
	//make cpu go 15MHz on TI-84 plus'es
	__asm
		in a,($02)
 		rlca
 		and %00000001
		out ($20),a
	__endasm
	/*
	puts("hold a key \n");
	sleep(2);
	unsigned char key = getCSC();
	puts("\n");
	printf(key);
	*/
	for(int i=0;i<13;i++)
	{
		set_pen_xy(i*4, 0);
		VPutMap(press[i]);
	}
	unsigned char key = getk();
	char num[3];
	set_pen_xy(40, 0);
	sprintf(num, "%d", key);
	for(int i=0;i<2;i++)
	{
		set_pen_xy(24+i*4, 10);
		VPutMap(num[i]);
	}
	set_pen_xy(72, 10);
	VPutMap(key);
	getk();
	return 0;
}
