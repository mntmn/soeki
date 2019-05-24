
; Maxon C++ Compiler
; Text:HiSOFT_C/projects/NetWor/Networ.c
	mc68030

	XREF	ChunKlear
	XREF	MouseButt
	XREF	ChunkyBlit
	XREF	UseChunk
	XREF	ChunkInit
	XREF	c2p030
	XREF	c2p030init
	XREF	_printf
	XREF	exit__i
	XREF	_AllocDBufInfo
	XREF	_ChangeVPBitMap
	XREF	_FreeBitMap
	XREF	_AllocBitMap
	XREF	_LoadRGB32
	XREF	_Read
	XREF	_Close
	XREF	_Open
	XREF	_ScreenToFront
	XREF	_OpenWindow
	XREF	_OpenScreen
	XREF	_CloseWindow
	XREF	_CloseScreen
	XREF	_FreeMem
	XREF	_AllocMem
	XREF	___MEMFLAGS
	XREF	_std__in
	XREF	_std__out
	XREF	_std__err

	SECTION ":0",CODE


	XDEF	LoadPalette__Store__TPc
LoadPalette__Store__TPc
L77	EQU	-$13BC
	link	a5,#L77+32
L78	EQU	$CFC
	movem.l	d2-d7/a2/a3,-(a7)
	moveq	#0,d4
	moveq	#0,d5
	move.l	$C(a5),a2
	pea	$3ED.w
	move.l	a2,-(a7)
	jsr	_Open
	addq.l	#$8,a7
	move.l	d0,d4
	pea	$33C.w
	pea	-$3F4(a5)
	move.l	d4,-(a7)
	jsr	_Read
	lea	$C(a7),a7
	move.l	d0,d5
	move.l	d4,-(a7)
	jsr	_Close
	addq.l	#4,a7
	tst.l	d4
	bne	L1
	pea	L79
	jsr	_printf
	addq.l	#4,a7
	move.l	$8(a5),-(a7)
	jsr	CleanUp__Store__T
	addq.l	#4,a7
	pea	$3EA.w
	jsr	exit__i
	addq.l	#4,a7
L1
	moveq	#$30,d2
	moveq	#0,d3
	bra	L3
L2
	move.l	d2,d7
	sub.l	#$2F,d7
	move.l	d7,d3
	lea	-$3F4(a5),a3
	moveq	#0,d7
	move.b	0(a3,d2.l),d7
	moveq	#$18,d6
	asl.l	d6,d7
	lea	-$1394(a5),a3
	move.l	d7,0(a3,d3.l*4)
	addq.l	#1,d2
L3
	cmp.l	#$32D,d2
	ble.b	L2
	lea	-$1394(a5),a3
	moveq	#0,d7
	move.l	#$FF0000,0(a3,d7.l*4)
	lea	-$1394(a5),a3
	move.l	#$2FF,d7
	clr.l	0(a3,d7.l*4)
	pea	-$1394(a5)
	move.l	$8(a5),a3
	add.l	#$84EC,a3
	move.l	(a3),d0

	END
