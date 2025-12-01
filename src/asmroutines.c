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