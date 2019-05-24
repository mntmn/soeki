

; Chunky FX library
; Copyright 1998 by mINUTEmAN/vTX
; C2P Unknown public source

; Index

	XDEF c2p030init
	XDEF c2p030
	XDEF ChunkInit
	XDEF UseChunk
	XDEF ChunkyBlit
	XDEF ChunkyBlitMix2
	XDEF MouseButt
	XDEF ChunKlear
	XDEF VWait
	XDEF ChunKopy

; - LoadChapes    {#num,name$}                       - Loads a blitz shape into a Chunky Shape
; - ChunkyBlit    {#num,x.l,y.l}                     - Supports clipping, cuts color 0
; - ChunkyMix     {chunky.l,x.w,y.w,table.l,w.w,h.w} - Rectangular color transparency
; - ChunkyBlitMix {#num,x.l,y.l,table.l}             - Mix of last two commands
; - ChunKopy      {source.l,dest.l,xoffs.w,yoffs.w}  - Copy a 320x256 buffer with offset

; Above parameters are not correct! Look into ChunkyLib.h for correct syntax!

; *********************************** Chape (Chunky Shape) Structure

;struct chape
;{
;  UBYTE w;
;  UBYTE h;
;  UBYTE xhandle;
;  UBYTE yhandle;
;  ULONG chunk.l;
;}

; *********************************** C2P routines

; c2p constants

c2pBPLX EQU 320
c2pBPLY EQU 256
c2pBPLSIZE EQU (c2pBPLX*c2pBPLY)/8
scrwidth EQU c2pBPLX
scrheight EQU c2pBPLY
screensize EQU scrwidth*scrheight

 Section code,CODE

c2p030init

  MOVEM.l d0-d6/a0-a6,-(a7)

  ;A.l=d0=Width.w
  ;B.l=d1=Height.w

; d0.w  chunkyx [chunky-pixels]
; d1.w  chunkyy [chunky-pixels]
; d2.w  (scroffsx) [screen-pixels]
; d3.w  scroffsy [screen-pixels]
; d4.w  (rowlen) [bytes] -- offset between one row and the next in a bpl
; d5.l  (c2pBPLSIZE) [bytes] -- offset between one row in one bpl and the next bpl

  MOVEQ.l #0,d2
  MOVEQ.l #0,d3
  MOVE.l  #c2pBPLX/8,d4
  MOVE.l  d4,d5
  MULU    d1,d5

  LEA c2p_datanew(pc),a0
  ANDI.l  #$ffff,d0
  MULU.w  d0,d3
  LSR.l #3,d3
  MOVE.l  d3,c2p_scroffs-c2p_data(a0)
  MULU.w  d0,d1
  MOVE.l  d1,c2p_pixels-c2p_data(a0)
  MOVEM.l (a7)+,d0-d6/a0-a6
 RTS

c2p030

  MOVE.l  d0,a0 ; Chunky
  MOVE.l  d1,a1 ; Planar

; a0  c2pscreen
; a1  bitplanes

c2p1x1_8_c5
  MOVEM.l d0-d6/a0-a6,-(a7)

  MOVEM.l a0-a1,-(a7)
  LEA c2p_datanew,a0
  LEA c2p_data,a1
  MOVEQ #16-1,d0
_copy: MOVE.l  (a0)+,(a1)+
  DBF d0,_copy
  MOVEM.l (a7)+,a0-a1

  LEA c2p_data(pc),a2

  MOVE.l  #$33333333,d5
  MOVE.l  #$55555555,d6
  MOVE.l  #$00ff00ff,a6

  ADD.w #c2pBPLSIZE,a1
  ADD.l c2p_scroffs-c2p_data(a2),a1

  MOVE.l  c2p_pixels-c2p_data(a2),a2
  ADD.l a0,a2
  CMP.l a0,a2
  BEQ _none

  MOVEM.l a0-a1,-(a7)

  MOVE.l  (a0)+,d0
  MOVE.l  (a0)+,d2
  MOVE.l  (a0)+,d1
  MOVE.l  (a0)+,d3

  MOVE.l  #$0f0f0f0f,d4   ; Merge 4x1, part 1
  AND.l d4,d0
  AND.l d4,d2
  LSL.l #4,d0
  OR.l  d2,d0

  AND.l d4,d1
  AND.l d4,d3
  LSL.l #4,d1
  OR.l  d3,d1

  MOVE.l  d1,a3

  MOVE.l  (a0)+,d2
  MOVE.l  (a0)+,d1
  MOVE.l  (a0)+,d3
  MOVE.l  (a0)+,d7

  AND.l d4,d2     ; Merge 4x1, part 2
  AND.l d4,d1
  LSL.l #4,d2
  OR.l  d1,d2

  AND.l d4,d3
  AND.l d4,d7
  LSL.l #4,d3
  OR.l  d7,d3

  MOVE.l  a3,d1

  MOVE.w  d2,d7     ; Swap 16x2
  MOVE.w  d0,d2
  SWAP  d2
  MOVE.w  d2,d0
  MOVE.w  d7,d2

  MOVE.w  d3,d7
  MOVE.w  d1,d3
  SWAP  d3
  MOVE.w  d3,d1
  MOVE.w  d7,d3

  BRA _start1
_x1
  MOVE.l  (a0)+,d0
  MOVE.l  (a0)+,d2
  MOVE.l  (a0)+,d1
  MOVE.l  (a0)+,d3

  MOVE.l  d7,c2pBPLSIZE(a1)

  MOVE.l  #$0f0f0f0f,d4   ; Merge 4x1, part 1
  AND.l d4,d0
  AND.l d4,d2
  LSL.l #4,d0
  OR.l  d2,d0

  AND.l d4,d1
  AND.l d4,d3
  LSL.l #4,d1
  OR.l  d3,d1

  MOVE.l  d1,a3

  MOVE.l  (a0)+,d2
  MOVE.l  (a0)+,d1
  MOVE.l  (a0)+,d3
  MOVE.l  (a0)+,d7

  MOVE.l  a4,(a1)+

  AND.l d4,d2     ; Merge 4x1, part 2
  AND.l d4,d1
  LSL.l #4,d2
  OR.l  d1,d2

  AND.l d4,d3
  AND.l d4,d7
  LSL.l #4,d3
  OR.l  d7,d3

  MOVE.l  a3,d1

  MOVE.w  d2,d7     ; Swap 16x2
  MOVE.w  d0,d2
  SWAP  d2
  MOVE.w  d2,d0
  MOVE.w  d7,d2

  MOVE.w  d3,d7
  MOVE.w  d1,d3
  SWAP  d3
  MOVE.w  d3,d1
  MOVE.w  d7,d3

  MOVE.l  a5,-c2pBPLSIZE-4(a1)
_start1
  MOVE.l  a6,d4

  MOVE.l  d2,d7     ; Swap 2x2
  LSR.l #2,d7
  EOR.l d0,d7
  AND.l d5,d7
  EOR.l d7,d0
  LSL.l #2,d7
  EOR.l d7,d2

  MOVE.l  d3,d7
  LSR.l #2,d7
  EOR.l d1,d7
  AND.l d5,d7
  EOR.l d7,d1
  LSL.l #2,d7
  EOR.l d7,d3

  MOVE.l  d1,d7
  LSR.l #8,d7
  EOR.l d0,d7
  AND.l d4,d7
  EOR.l d7,d0
  LSL.l #8,d7
  EOR.l d7,d1

  MOVE.l  d1,d7
  LSR.l #1,d7
  EOR.l d0,d7
  AND.l d6,d7
  EOR.l d7,d0
  MOVE.l  d0,c2pBPLSIZE*2(a1)
  ADD.l d7,d7
  EOR.l d1,d7

  MOVE.l  d3,d1
  LSR.l #8,d1
  EOR.l d2,d1
  AND.l d4,d1
  EOR.l d1,d2
  LSL.l #8,d1
  EOR.l d1,d3

  MOVE.l  d3,d1
  LSR.l #1,d1
  EOR.l d2,d1
  AND.l d6,d1
  EOR.l d1,d2
  ADD.l d1,d1
  EOR.l d1,d3

  MOVE.l  d2,a4
  MOVE.l  d3,a5

  CMPA.l  a0,a2
  BNE _x1

  MOVE.l  d7,c2pBPLSIZE(a1)
  MOVE.l  a4,(a1)+
  MOVE.l  a5,-c2pBPLSIZE-4(a1)

  MOVEM.l (a7)+,a0-a1
  ADD.l #c2pBPLSIZE*4,a1

  MOVE.l  (a0)+,d0
  MOVE.l  (a0)+,d2
  MOVE.l  (a0)+,d1
  MOVE.l  (a0)+,d3

  MOVE.l  #$f0f0f0f0,d4   ; Merge 4x1, part 1
  AND.l d4,d0
  AND.l d4,d2
  LSR.l #4,d2
  OR.l  d2,d0

  AND.l d4,d1
  AND.l d4,d3
  LSR.l #4,d3
  OR.l  d3,d1

  MOVE.l  d1,a3

  MOVE.l  (a0)+,d2
  MOVE.l  (a0)+,d1
  MOVE.l  (a0)+,d3
  MOVE.l  (a0)+,d7

  AND.l d4,d2     ; Merge 4x1, part 2
  AND.l d4,d1
  LSR.l #4,d1
  OR.l  d1,d2

  AND.l d4,d3
  AND.l d4,d7
  LSR.l #4,d7
  OR.l  d7,d3

  MOVE.l  a3,d1

  MOVE.w  d2,d7     ; Swap 16x2
  MOVE.w  d0,d2
  SWAP  d2
  MOVE.w  d2,d0
  MOVE.w  d7,d2

  MOVE.w  d3,d7
  MOVE.w  d1,d3
  SWAP  d3
  MOVE.w  d3,d1
  MOVE.w  d7,d3

  BRA _start2
_x2
  MOVE.l  (a0)+,d0
  MOVE.l  (a0)+,d2
  MOVE.l  (a0)+,d1
  MOVE.l  (a0)+,d3

  MOVE.l  d7,c2pBPLSIZE(a1)

  MOVE.l  #$f0f0f0f0,d4   ; Merge 4x1, part 1
  AND.l d4,d0
  AND.l d4,d2
  LSR.l #4,d2
  OR.l  d2,d0

  AND.l d4,d1
  AND.l d4,d3
  LSR.l #4,d3
  OR.l  d3,d1

  MOVE.l  d1,a3

  MOVE.l  (a0)+,d2
  MOVE.l  (a0)+,d1
  MOVE.l  (a0)+,d3
  MOVE.l  (a0)+,d7

  MOVE.l  a4,(a1)+

  AND.l d4,d2     ; Merge 4x1, part 2
  AND.l d4,d1
  LSR.l #4,d1
  OR.l  d1,d2

  AND.l d4,d3
  AND.l d4,d7
  LSR.l #4,d7
  OR.l  d7,d3

  MOVE.l  a3,d1

  MOVE.w  d2,d7     ; Swap 16x2
  MOVE.w  d0,d2
  SWAP  d2
  MOVE.w  d2,d0
  MOVE.w  d7,d2

  MOVE.w  d3,d7
  MOVE.w  d1,d3
  SWAP  d3
  MOVE.w  d3,d1
  MOVE.w  d7,d3

  MOVE.l  a5,-c2pBPLSIZE-4(a1)
_start2
  MOVE.l  a6,d4

  MOVE.l  d2,d7     ; Swap 2x2
  LSR.l #2,d7
  EOR.l d0,d7
  AND.l d5,d7
  EOR.l d7,d0
  LSL.l #2,d7
  EOR.l d7,d2

  MOVE.l  d3,d7
  LSR.l #2,d7
  EOR.l d1,d7
  AND.l d5,d7
  EOR.l d7,d1
  LSL.l #2,d7
  EOR.l d7,d3

  MOVE.l  d1,d7
  LSR.l #8,d7
  EOR.l d0,d7
  AND.l d4,d7
  EOR.l d7,d0
  LSL.l #8,d7
  EOR.l d7,d1

  MOVE.l  d1,d7
  LSR.l #1,d7
  EOR.l d0,d7
  AND.l d6,d7
  EOR.l d7,d0
  MOVE.l  d0,c2pBPLSIZE*2(a1)
  ADD.l d7,d7
  EOR.l d1,d7

  MOVE.l  d3,d1
  LSR.l #8,d1
  EOR.l d2,d1
  AND.l d4,d1
  EOR.l d1,d2
  LSL.l #8,d1
  EOR.l d1,d3

  MOVE.l  d3,d1
  LSR.l #1,d1
  EOR.l d2,d1
  AND.l d6,d1
  EOR.l d1,d2
  ADD.l d1,d1
  EOR.l d1,d3

  MOVE.l  d2,a4
  MOVE.l  d3,a5

  CMPA.l  a0,a2
  BNE _x2

  MOVE.l  d7,c2pBPLSIZE(a1)
  MOVE.l  a4,(a1)+
  MOVE.l  a5,-c2pBPLSIZE-4(a1)

_none
  MOVEM.l (a7)+,d0-d6/a0-a6
  BRA asm_endc2p

  Even
c2p_data
c2p_scroffs: Dc.l 0
c2p_pixels: Dc.l 0
  Ds.l  16
  Even
c2p_datanew
  Ds.l  16
asm_endc2p
 RTS

; *********************************** Init

ChunkInit

  ; d0 = ChapesBase.l
  ; d1 = CLUT.l

  MOVE.l d0,_ChapesBase
  MOVE.l d1,_CLUT
 RTS

UseChunk

  ; d0 = ChunkyBuf.l

  MOVE.l d0,_ChunkyBuf
 RTS

; *********************************** Chape drawing

ChunkyBlit

  ; d0 = shp.w
  ; d1 = x.l
  ; d2 = y.l

  MOVEM.l d0-d6/a0-a6,-(a7)

  MOVE.l _ChapesBase,a0
  MULU.w #8,d0
  ADD.l d0,a0
  MOVE.l _ChunkyBuf,a1
                
  EXG.l  d0,d1
  EXG.l  d1,d2

  CLR.w  d2
  CLR.w  d3
  CLR.w  d4
  CLR.w  d5

  MOVE.b 2(a0),d4
  MOVE.b 3(a0),d5

  SUB.w  d4,d0
  SUB.w  d5,d1

  MOVE.b (a0),d4
  MOVE.b 1(a0),d5
  MOVE.b d4,d2
  MOVE.b d5,d3

  ADD.w  d0,d4                ; x+w => ox
  ADD.w  d1,d5                ; y+h => oy

  TST.w  d0                ; if x<0
  BMI    asm_jumpoint         ; then skip

  CMP.w  #319,d4              ; if ox not >319
  BLS    asm_chekpoint        ; then skip
  MOVE.w #319,d4              ; else
  SUB.w  d0,d4                ; ox=319-x
  JMP    asm_jumpoint         ; skip

asm_chekpoint
  MOVE.w d2,d4                ; w => ox

asm_jumpoint

  TST.w  d1                ; if y<0
  BMI    asm_jumpoint2        ; then skip

  CMP.w  #255,d5              ; if oy not >255
  BLS    asm_chekpoint2       ; then skip
  MOVE.w #255,d5              ; else
  SUB.w  d1,d5                ; oy=255-y
  JMP    asm_jumpoint2        ; skip

asm_chekpoint2
  MOVE.w d3,d5                ; h => oy

asm_jumpoint2

  MOVE.l 4(a0),a2             ; datapointer => adr

  TST.w  d0                   ; if x>-1
  BPL    asm_chekpoint3       ; then skip
  MOVE.l #0,d0                ; x=0
  CLR.l  d6                   ;
  MOVE.b (a0),d6              ; w2=w
  SUB.w  d4,d6                ; w2=w-ox
  ADD.l  d6,a2                ; adr+w2
asm_chekpoint3

  TST.w  d1
  BPL    asm_chekpoint4
  MOVE.l #0,d1
  CLR.l  d6
  MOVE.b 1(a0),d6
  SUB.b  d5,d6
  ADDQ   #1,d2
  MULU.w d2,d6
  SUBQ   #1,d2
  ADD.l  d6,a2
asm_chekpoint4

  MULU.w #320,d1
  ADD.l  d1,d0
  ADD.l  d0,a1

  MOVE.l #319,d6
  SUB.w  d4,d6

  MOVE.b (a0),d3
  SUB.b  d4,d3

  CMP.w #1,d4
  BLE   asm_breakout
  CMP.w #1,d5
  BLE   asm_breakout

asm_yloop2
    MOVE.l d4,d2
asm_xloop2
      MOVE.b (a2)+,d0
      CMP.b #0,d0
      BEQ.b asm_backcut
      MOVE.b d0,(a1)
asm_backcut
      ADDQ  #1,a1
    DBRA d2,asm_xloop2
    ADD.w d6,a1
    ADD.w d3,a2
  DBRA d5,asm_yloop2

asm_breakout
  MOVEM.l (a7)+,d0-d6/a0-a6
 RTS

; *********************************** Rectangular Transparency

ChunkyMix

  ; d1 = x.w
  ; d2 = y.w
  ; d4 = w.w
  ; d5 = h.w
  ; d0 = c.w

  MOVEM.l d0-d7/a0-a6,-(a7)

  MOVE.l d0,a0
  LEA _ChunkyBuf,a2

  CLR.l  d0

  MOVE.w d2,d0
  MULU.w #320,d0

  ADD.w  d1,d0

  ADD.l  d0,a0

  ;CLR.l  d1
  ;CLR.l  d2
  CLR.l  d3

  MOVE.w d4,d1
asm_yloop5
    MOVE.w d5,d2
    MOVE.l a0,a1
asm_xloop5
      MOVE.l a2,a3
      MOVE.b (a1),d3
      ADD.l  d3,a3
      MOVE.b (a3),(a1)+
    DBRA d2,asm_xloop5
    ADD.w #320,a0
  DBRA d1,asm_yloop5

  MOVEM.l (a7)+,d0-d7/a0-a6
 RTS

; *********************************** Chape Transparency

ChunkyBlitMix 

  ; d0 = shp.w
  ; d1 = x.l
  ; d2 = y.l
 
  MOVEM.l d0-d6/a0-a6,-(a7)

  MOVE.l _ChapesBase,a0
  MULU.w #8,d0
  ADD.l d0,a0
  MOVE.l _ChunkyBuf,a1

  EXG.l  d0,d1
  EXG.l  d1,d2

  MOVE.l _CLUT,a3

  CLR.w  d2
  CLR.w  d3
  CLR.w  d4
  CLR.w  d5

  MOVE.b 2(a0),d4
  MOVE.b 3(a0),d5

  SUB.w  d4,d0
  SUB.w  d5,d1

  MOVE.b (a0),d4
  MOVE.b 1(a0),d5
  MOVE.b d4,d2
  MOVE.b d5,d3

  ADD.w  d0,d4
  ADD.w  d1,d5

  CMP.w  #0,d0
  BLT    asm_jumpoint5

  CMP.w  #319,d4
  BLS    asm_chekpoint5
  MOVE.w #319,d4
  SUB.w  d0,d4
  JMP    asm_jumpoint5

asm_chekpoint5
  MOVE.w d2,d4

asm_jumpoint5

  CMP.w  #0,d1
  BLT    asm_jumpoint6

  CMP.w  #255,d5
  BLS    asm_chekpoint6
  MOVE.w #255,d5
  SUB.w  d1,d5
  JMP    asm_jumpoint6

asm_chekpoint6
  MOVE.w d3,d5

asm_jumpoint6

  MOVE.l 4(a0),a2

  CMP.w  #-1,d0
  BGT    asm_chekpoint7
  MOVE.w #0,d0
  CLR.l  d6
  MOVE.b (a0),d6
  SUB.w  d4,d6
  ADD.l  d6,a2
asm_chekpoint7

  CMP.w  #-1,d1
  BGT    asm_chekpoint8
  MOVE.w #0,d1
  CLR.l  d6
  MOVE.b 1(a0),d6
  SUB.b  d5,d6
  ADDQ   #1,d2
  MULU.w d2,d6
  SUBQ   #1,d2
  ADD.l  d6,a2
asm_chekpoint8

  MULU.w #320,d1
  ADD.l  d1,d0
  ADD.l  d0,a1

  MOVE.l #319,d6
  SUB.w  d4,d6

  MOVE.b (a0),d3
  SUB.b  d4,d3

  MOVEQ #0,d0

asm_yloop3
    MOVE.l d4,d2
asm_xloop3
      MOVE.b (a2)+,d0
      CMP.b #0,d0
      BEQ.b asm_backcut2

      MOVE.l a3,a4
      MOVE.b (a1),d0
      ADD.l  d0,a4
      MOVE.b (a4),(a1)

asm_backcut2
      ADDQ  #1,a1
    DBRA d2,asm_xloop3
    ADD.w d6,a1
    ADD.w d3,a2
  DBRA d5,asm_yloop3

  MOVEM.l (a7)+,d0-d6/a0-a6
 RTS

ChunkyBlitMix2

  ; d0 = x.l
  ; d1 = y.l
  ; d2 = shp.w

  MOVEM.l a0-a6,-(a7)

  MOVE.l _ChapesBase,a0
  MULU.w #8,d0
  ADD.l d0,a0
  MOVE.l _ChunkyBuf,a1

  EXG.l  d0,d1
  EXG.l  d1,d2

  MOVE.l _CLUT,a3

  CLR.w  d2
  CLR.w  d3
  CLR.w  d4
  CLR.w  d5

  MOVE.b 2(a0),d4
  MOVE.b 3(a0),d5

  SUB.w  d4,d0
  SUB.w  d5,d1

  MOVE.b (a0),d4
  MOVE.b 1(a0),d5
  MOVE.b d4,d2
  MOVE.b d5,d3

  ADD.w  d0,d4
  ADD.w  d1,d5

  CMP.w  #0,d0
  BLT    asm_jumpoint52

  CMP.w  #319,d4
  BLS    asm_chekpoint52
  MOVE.w #319,d4
  SUB.w  d0,d4
  JMP    asm_jumpoint52

asm_chekpoint52
  MOVE.w d2,d4

asm_jumpoint52

  CMP.w  #0,d1
  BLT    asm_jumpoint62

  CMP.w  #255,d5
  BLS    asm_chekpoint62
  MOVE.w #255,d5
  SUB.w  d1,d5
  JMP    asm_jumpoint62

asm_chekpoint62
  MOVE.w d3,d5

asm_jumpoint62

  MOVE.l 4(a0),a2

  CMP.w  #-1,d0
  BGT    asm_chekpoint72
  MOVE.w #0,d0
  CLR.l  d6
  MOVE.b (a0),d6
  SUB.w  d4,d6
  ADD.l  d6,a2
asm_chekpoint72

  CMP.w  #-1,d1
  BGT    asm_chekpoint82
  MOVE.w #0,d1
  CLR.l  d6
  MOVE.b 1(a0),d6
  SUB.b  d5,d6
  ADDQ   #1,d2
  MULU.w d2,d6
  SUBQ   #1,d2
  ADD.l  d6,a2
asm_chekpoint82

  MULU.w #320,d1
  ADD.l  d1,d0
  ADD.l  d0,a1

  MOVE.l #319,d6
  SUB.w  d4,d6

  MOVE.b (a0),d3
  SUB.b  d4,d3

  MOVEQ #0,d0

asm_yloop32
    MOVE.l d4,d2
asm_xloop32
      MOVE.l #0,d0
      MOVE.b (a2)+,d0
      CMP.b #0,d0
      BEQ.b asm_backcut22

      MULU.w #512,d0
      MOVE.l a3,a4
      ADD.l  d0,a4
      MOVE.l  #0,d0
      MOVE.b (a1),d0
      ADD.l  d0,a4
      MOVE.b (a4),(a1)

asm_backcut22
      ADDQ  #1,a1
    DBRA d2,asm_xloop32
    ADD.w d6,a1
    ADD.w d3,a2
  DBRA d5,asm_yloop32

  MOVEM.l (a7)+,a0-a6
 RTS

; ****************************** Usefull Stuff

MouseButt:
  MOVE.b	$bfe001,d0
  ANDI.b	#$40,d0
  OR.b	#$BF,d0
  NOT.b	d0
 RTS

ChunKlear:
  MOVEM.l d0/a0,-(a7)
  MOVE.l _ChunkyBuf,a0
  MOVE.l #(320*256)/4-1,d0
asm_klearloop
  MOVE.l #0,(a0)+
  DBRA d0,asm_klearloop
  MOVEM.l (a7)+,d0/a0
 RTS
 
ChunKopy:
  MOVEM.l d0/a0-a1,-(a7)
  MOVE.l #(320*256)/4-1,d0
asm_kopyloop
  MOVE.l (a0)+,(a1)+
  DBRA d0,asm_kopyloop
  MOVEM.l (a7)+,d0/a0-a1
 RTS
 
VWait:
  MOVEM.l d0,-(a7)
  MOVE.b #0,d0
asm_vwloop
  MOVE.b $dff006,d0
  CMP.b #60,d0
  BNE asm_vwloop
  MOVEM.l (a7)+,d0
 RTS

; Globally needed stuff

 Section Stuff,DATA

_ChapesBase dc.l 0
_ChunkyBuf  dc.l 0
_CLUT       dc.l 0

 END
