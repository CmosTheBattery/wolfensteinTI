void clgblack()
{
	//HACK : yeahh
	putsprite(SPR_OR,0,0,spr_black);
	//funny thing this used to write directly to lcd ram
	//and that caused problems

	//TODO : this shit doesn't work
	/*
	__asm
		ld hl, $9340       ; Address of plotSScreen
		ld c,$03		   ; Y loop counter (rows)
	loopy:
		ld a,c
		ld b,$FF		   ; X loop counter (columns)
		ld a,$FF		   ; B L A C K
	loopx:
		ld (hl), a
		inc hl
		djnz loopx
		dec c
		jp p,loopy
	;CTRL+C CTRL+V
	fastCopy:
		di
		ld a,$80
		out ($10),a
		ld hl, $9340-12-(-(12*64)+1)
		ld a,$20
		ld c,a
		inc hl
		dec hl
	fastCopyAgain:
		ld b,64
		inc c
		ld de,-(12*64)+1
		out ($10),a
		add hl,de
		ld de,10
	fastCopyLoop:
		add hl,de
		inc hl
		inc hl
		inc de
		ld a,(hl)
		out ($11),a
		dec de
		djnz fastCopyLoop
		ld a,c
		cp $2B+1
		jr nz,fastCopyAgain
		ret	   
	__endasm
	*/
}

static uint8_t getCSC(void) __naked
{
	__asm
		rst  0x28 ; bcall dispatcher
		defw 0x4018 ; _GetCSC
		ld   l,a ; return value -> HL
		ld   h,0
		ret
	__endasm;
}

// From ti83plus.inc: addresses of penCol and penRow
#define PEN_COL_ADDR 0x86D7
#define PEN_ROW_ADDR 0x86D8

//KINDA HACKY : seperate cursor and vputmap
void set_pen_xy(uint8_t x, uint8_t y)
{
	*(volatile uint8_t*)PEN_COL_ADDR = x;   // penCol
	*(volatile uint8_t*)PEN_ROW_ADDR = y;   // penRow
}

void VPutMap(char c)
{
	__asm
		ld   hl, 2
		add  hl, sp
		ld   a, (hl) ; A = c
		rst  0x28
		defw 0x455E ; VPutMap BCALL
	__endasm
}

void changeLCDz(uint8_t s)
{
	__asm
		push bc
		ld b, $40 ;s is in register A
		add a, b
		out ($10), a
		pop bc
		call $000B
	__endasm
}

