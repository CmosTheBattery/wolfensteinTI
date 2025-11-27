#pragma string name KEYTEST

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <graphics.h>
#include <games.h>

#include <src/icons.h>


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

// From ti83plus.inc: addresses of penCol and penRow
#define PEN_COL_ADDR 0x86D7  // (pencol) in TI-83+ / TI-84+ OS :contentReference[oaicite:0]{index=0}  
#define PEN_ROW_ADDR 0x86D8  // (penrow) :contentReference[oaicite:1]{index=1}  

void set_pen_xy(uint8_t x, uint8_t y) {
    *(volatile uint8_t*)PEN_COL_ADDR = x;   // penCol
    *(volatile uint8_t*)PEN_ROW_ADDR = y;   // penRow
}

void vputmap(char c) {
    __asm
        ld   hl, 2
        add  hl, sp
        ld   a, (hl)          ; A = c
        rst  0x28
        defw  0x455E           ; VPutMap BCALL
    __endasm;
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
		set_pen_xy(i*4, 5);
		vputmap(i+65);
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
