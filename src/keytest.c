#pragma string name KEYTEST

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <graphics.h>
#include <games.h>

#include <icons.h>


void clgblack()
{
	//inline asm always gets the job done 'Oᴗ-'
	//and can soft lock the calculator 'O_O'
	//TODO : ts doesn't work sometimes
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

		ld a,$02		   ; LCD off (avoid weird effect)
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

		ld a,$03		   ; LCD on
		out ($10),a
		call $000B
		
		pop bc
		pop af
		ret
	__endasm
}

static uint8_t getCSC(void) __naked {
    __asm
        rst  0x28          ; bcall dispatcher
        defw 0x4018        ; _GetCSC
        ld   l,a           ; return value -> HL
        ld   h,0
        ret
    __endasm;
}

void drawChar(uint8_t x, uint8_t y, uint8_t idx)
{
	char* selected;
	switch(idx)
	{
		case 1:
			selected=font_A;
			break;
		case 2:
			selected=font_B;
			break;
		case 3:
			selected=font_C;
			break;
		case 4:
			selected=font_D;
			break;
		case 5:
			selected=font_E;
			break;
		case 6:
			selected=font_F;
			break;
		case 7:
			selected=font_G;
			break;
		case 8:
			selected=font_H;
			break;
		case 9:
			selected=font_I;
			break;
		case 10:
			selected=font_J;
			break;
		default:
			selected=font_blank;
			break;
	}
	putsprite(SPR_OR,x,y,selected);
}

int main()
{
	/*
	puts("hold a key \n");
	sleep(2);
	unsigned char key = getCSC();
	puts("\n");
	printf(key);
	*/
	for(int i=0;i<11;i++)
	{
		drawChar(i*4, 5, i);
	}
	getk();
	clgblack();
	getk();
	return 0;
}

/*
	.org 9D93h
	.db 0BBh, 6Bh
		rst 28h ; B_CALL
		dw  4540h ; ClrScrnFull
		ld  (hl), 0
		ld  (844Bh), hl
		rst 28h ; B_CALL
		dw  4972h ; GetKey
		ld h, 0
		ld l, a
		rst 28h ; B_CALL
		dw  4507h ; DispHL
		ret
*/
