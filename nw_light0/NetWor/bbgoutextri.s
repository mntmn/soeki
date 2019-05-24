
 XDEF textri
 XDEF textriinit

 SECTION code,CODE


;******************************************************
;*       Some Macros            *
;******************************************************

def9l MACRO var1,var2,var3,var4,var5,var6,var7,var8,var9
\1 dc.l 0
\2 dc.l 0
\3 dc.l 0
\4 dc.l 0
\5 dc.l 0
\6 dc.l 0
\7 dc.l 0
\8 dc.l 0
\9 dc.l 0
 ENDM

Tausch MACRO Var1, Var2
 move.l \1-Vars(a1),D0
 move.l \2-Vars(a1),D1
; exg.l D0,D1
 move.l D0,\2-Vars(a1)
 move.l D1,\1-Vars(a1)
 ENDM

Round MACRO Var1
 add.l #128,\1
 asr.l #8,\1
 ENDM

Round2 MACRO Var1
 add.l #128,\1
 and.l #$ffffff00,\1
 ENDM

xw1 equr D4
xw2 equr D5
zw1 equr D6
zw2 equr D7
zw equr D2

cz equr D2
sz equr D3

;***************************************************************
;*       Texline                *
;***************************************************************

Texline MACRO
;Beachten: cz,sz,xw1,xw2,zw1,zw2 befinden sich in dieser Reihenfolge in d2-d7
;Jetzt können diese Regs mitgenutzt werden, wegen movem:
 movem.l d2-d7,-(sp)  ;Regs sichern
 move.w sz,y-vars(a1)   ;aufheben für später

; --- Clipping Part 1 ---
 cmp.w #255,sz  ;sz>255?
 bgt sl03\@      ;wenn 2. Operand (x2) größer ist, dann raus
 cmp.w #1,sz     ;sz<0
 blt sl03\@      ;ja -> raus

 move.l xw1,d0  ;d4,d0          D0  D1  D2      D3  D4  D5      D6  D7
 move.l xw2,d1  ;d5,d1          xw1 xw2 zw1 zw2 xw1 xw2 zw1 zw2
 move.l zw1,d2  ;d6,d2
 move.l zw2,d3  ;d7,d3
 move.l txw1-Vars(a1),d4        ;               xw1 xw2 zw1 zw2 txw1txw2tyw1tyw2
 move.l txw2-Vars(a1),d5
 move.l tyw1-Vars(a1),d6
 move.l tyw2-Vars(a1),d7
 cmp.l  d0,d1    ;xw1>xw2
 bge.s sl01\@
  exg.l d0,d1    ;if x1>x2 then Tausche x1 mit x2 und
  exg.l d2,d3    ;z1 mit z2
  exg.l d4,d5    ;txw1<->txw2
  exg.l d6,d7    ;tyw1<->tyw2
sl01\@:

;Sichern Teil 1
 move.l d4,tx1-Vars(a1)
 move.l d5,tx2-Vars(a1)
 move.l d6,ty1-Vars(a1)
 move.l d7,ty2-Vars(a1)


; --- Clipping Part 2 ---
 cmp.l #319<<8,d1  ;x2>319?
 ble.s cl0\@     ;wenn 2. Operand (x2) kleiner ist, dann hops
 move.l #319<<8,d1
cl0\@:
 cmp.l #0,d1     ;x2<0
 ble sl03\@      ;ja -> raus
 cmp.l #319<<8,d0  ;x1>319?
 bgt sl03\@      ;ja -> raus

;Sichern Teil 2
 move.l d0,x1-Vars(a1)   ;und sichern           x1  x2  z1      z2
 move.l d1,x2-Vars(a1)
 move.l d2,z1-Vars(a1)
 move.l d3,z2-Vars(a1)

 sub.l d2,d3    ;z2-z1 -> d3
 move.l d3,zd-Vars(a1)   ;zd:=z2-z1  {Abstand zw. Z}    x1  x2  z1      zd
 add.l #256,d1  ;runden
 sub.l d0,d1    ;x2-x1 -> d1
 move.l d1,xd-Vars(a1)   ;              x1  xd  z1      zd

 or.l d1,d1
 beq sl02\@  ;if xd>0 then (Wenn mehr als 1 Pixel)

 asl.l #8,d3    ;zs ausrechnen
 divs.l d1,d3   ;               zs=zd/xd
 move.l d3,zs-Vars(a1)  ;               x1  xd  z1      zs
        ;               d0  d1  d2      d3
 sub.l d4,d5     ;tx2-tx1 -> d5
; move.l d5,txd-Vars(a1)  ;txd=tx2-tx1
 sub.l d6,d7     ;ty2-ty1 -> tyd
; move.l d7,tyd-Vars(a1)

 move.l txs-Vars(a1),d5
 move.l tys-Vars(a1),d7

; asl.l #8,d5
; divs.l d1,d5    ;txd/xd
; move.l d5,txs-Vars(a1)
; asl.l #8,d7
; divs.l d1,d7    ;tyd/xd
; move.l d7,tys-Vars(a1)

;Clipping Part 3
;x1 ist immer noch in d0, xd in d1
;d0/1/3/5 dürfen verändert werden wegen unten
 cmp.l #0,d0     ;x1<0?
 bge.s cl1\@
 neg.l d0
; asr.l #8,d0 ;auf Bildschirmgenauigkeit - evtl. runden
 move.l d5,d1 ;txs s.o.
 muls.l d0,d1 ;txs*(-x1)
 asr.l #8,d1
 add.l d1,tx1-Vars(a1)  ;txw+txs*(-x1)
 move.l d7,d1 ;tys s.o.
 muls.l d0,d1 ;tys*(-x1)
 asr.l #8,d1
 add.l d1,ty1-Vars(a1)  ;tyw+tys*(-x1)
 move.l d3,d1 ;zs s.o.
 muls.l d0,d1 ;zs*(-x1)
 asr.l #8,d1
 add.l d1,d3  ;zw+zs*(-x1)
 moveq.l #0,d0   ;x1=0 - hier muß noch tex-x und -y und z korrigiert werden
 move.l d0,x1-Vars(a1)
cl1\@:


 ;durch obige Definition ist zw=z1 (zw=Startpunkt z)
 move.w y-Vars(a1),d0    ;              y        xd  z1 zs
 mulu.w #320,d0
 move.l x1-Vars(a1),d1   ;              y        x1  z1 zs
 Round d1
 add.w d1,d0  ;y*320+x           Scrofs
; lea ChunkyBuf,a3
 move.l ChunkyBuf-Vars(a1),a3
 lea (a3,d0.l),a3 ;a3 ist nun Screenadresse
; move.l FZBuf-Vars(a1),a4
; lea (a4,d0.l*2),a4 ;a4 ist nun ZBufadresse
 move.l CCTab-Vars(a1),a5
; move.l Tribright-Vars(a1),d0
; lsl.w #8,d0  ;*256 für die Helligkeitsstufen
; lea (a5,d0.w),a5  ;ATdresse für Colorconverttab

        move.l ty1-Vars(a1),d3  ;Optimieren!!!
;        Round d3
        move.l tx1-Vars(a1),d5
;        Round d5

        move.l txs-Vars(a1),d6
        move.l tys-Vars(a1),d4
        move.l TexMap-Vars(a1),a2

        move.l x2-Vars(a1),d0
        Round d0

        move.l x1,d1    ;               x2  x1  z1      zs
        Round d1

        sub.l  d1,d0    ;x2-x1 -> d4 ist Schleifenzähler = xd !!! Optimieren!
        move.l d0,d7    ;               cnt x1  z1      zs       cnt

        ;zw ist in d2 ;(esi)            cnt zs  zw       cnt
        move.l zs-Vars(a1),a4  ;war mal FZBuf, wird aber hier nicht gebraucht
        moveq.l #0,d0

sl02\@           ;      fr  fr  fr      d3  d4  d5      d6  d7
        ;move.l d5,d1
        move.w d5,d1
        move.w d3,d0
        asr.w #8,d1
        add.l  d4,d3  ;tyw+tys - wegen Pipeline hierher
        move.b d1,d0  ;yyyyyyyy xxxxxxxx
        add.l d6,d5 ;txw+txs
        move.w d2,d1 ;zw->d1   ....ZZZZzzzzzzzz
        move.b (a2,d0.l),d1  ; ....ZZZZcccccccc
        add.l a4,d2   ;zw+=zs
        move.b (a5,d1.w),(a3)+  ;colorconverted
        ;move.b #47,(a3)+
        dbf d7,sl02\@
sl03\@
        movem.l (sp)+,d2-d7
 ENDM

;*******************************************************
;*        Textri         *
;*******************************************************

textri
 movem.l d0-d7/a0-a6,-(sp)

 lea TexMap,a1

 lea rtax,a4
 lea tax,a5
 move.w #6-1,d7
tcop
 move.l (a4)+,(a5)+
 dbf d7,tcop

 move.l pay-vars(a1),d0 ;Ab hier werden die 3 Punkte nach y sortiert
 move.l pby-vars(a1),d1
 cmp.l  d0,d1
 bge.s  Tdr01
  move.l d1,pay-vars(a1)
  move.l d0,pby-vars(a1)
  Tausch pax,pbx
  Tausch paz,pbz
  Tausch tax,tbx
  Tausch tay,tby
Tdr01:
 move.l pby-Vars(a1),d0
 move.l pcy-Vars(a1),d1
 cmp.l  d0,d1
 bge.s  Tdr02
  move.l d1,pby-Vars(a1)
  move.l d0,pcy-Vars(a1)
  Tausch pbx,pcx
  Tausch pbz,pcz
  Tausch tbx,tcx
  Tausch tby,tcy
Tdr02:
 move.l pay-Vars(a1),d0
 move.l pby-Vars(a1),d1
 cmp.l  d0,d1
 bge.s  Tdr03
  move.l d1,pay-Vars(a1)
  move.l d0,pby-Vars(a1)
  Tausch pax,pbx
  Tausch paz,pbz
  Tausch tax,tbx
  Tausch tay,tby ;Ende Sort
Tdr03:

  lea pax(pc),a0  ;Punktwerte nochmal runden
  move.w #9-1,d1
LSTrloop
  move.l (a0),d0
  Round2 d0
  move.l d0,(a0)+
  dbf d1,LSTrloop

;Deltaberechnung
  move.l pbx-Vars(a1),d0
  sub.l pax-Vars(a1),d0
  move.l d0,xd1-Vars(a1)

  move.l pcx-Vars(a1),d0
  sub.l pax-Vars(a1),d0
  move.l d0,xd2-Vars(a1)

  move.l pcx-Vars(a1),d0
  sub.l pbx-Vars(a1),d0
  move.l d0,xd3-Vars(a1)

  move.l pby-Vars(a1),d1
  sub.l pay-Vars(a1),d1
  move.l d1,yd1-Vars(a1)

  move.l pcy-Vars(a1),d2
  sub.l pay-Vars(a1),d2
  move.l d2,yd2-Vars(a1)

  move.l pcy-Vars(a1),d3
  sub.l pby-Vars(a1),d3
  move.l d3,yd3-Vars(a1)

  move.l pbz-Vars(a1),d0
  sub.l paz-Vars(a1),d0
  move.l d0,zd1-Vars(a1)

  move.l pcz-Vars(a1),d0
  sub.l paz-Vars(a1),d0
  move.l d0,zd2-Vars(a1)

  move.l pcz-Vars(a1),d0
  sub.l pbz-Vars(a1),d0
  move.l d0,zd3-Vars(a1)

;Texturemap
  move.l tbx-Vars(a1),d0
  sub.l tax-Vars(a1),d0
  move.l d0,txd1-Vars(a1)

  move.l tcx-Vars(a1),d0
  sub.l tax-Vars(a1),d0
  move.l d0,txd2-Vars(a1)

  move.l tcx-Vars(a1),d0
  sub.l tbx-Vars(a1),d0
  move.l d0,txd3-Vars(a1)

  move.l tby-Vars(a1),d0
  sub.l tay-Vars(a1),d0
  move.l d0,tyd1-Vars(a1)

  move.l tcy-Vars(a1),d0
  sub.l tay-Vars(a1),d0
  move.l d0,tyd2-Vars(a1)

  move.l tcy-Vars(a1),d0
  sub.l tby-Vars(a1),d0
  move.l d0,tyd3-Vars(a1)
;Deltaberechnung Ende

;yd1-yd3 runden
  Round d1
  Round d2
  Round d3

;Stepberechnung
  or.l d1,d1     ;yd1<>0
  beq.s Tdr04
        move.l xd1-Vars(a1),d0    ;XDelta1
        divs.l d1,d0 ;xs1=xd1/yd1
        move.l d0,xs1-Vars(a1)    ;XStep1

        move.l zd1-Vars(a1),d0
        divs.l d1,d0 ;zs1=zd1/yd1
        move.l d0,zs1-Vars(a1)

        move.l txd1-Vars(a1),d0
        divs.l d1,d0 ;txs1=txd1/yd1
        move.l d0,txs1-Vars(a1)

        move.l tyd1-Vars(a1),d0
        divs.l d1,d0 ;tys1=tyd1/yd1
        move.l d0,tys1-Vars(a1)

        bra.s  Tdr05
Tdr04:
        move.l xd1-Vars(a1),xs1-Vars(a1)
        move.l zd1-Vars(a1),zs1-Vars(a1)
        move.l txd1-Vars(a1),txs1-Vars(a1)
        move.l tyd1-Vars(a1),tys1-Vars(a1)
Tdr05:

  or.l d2,d2     ;yd2<>0
  beq.s Tdr06
        move.l xd2-Vars(a1),d0
        divs.l d2,d0 ;xs2=xd2/yd2
        move.l d0,xs2-Vars(a1)

        move.l zd2-Vars(a1),d0
        divs.l d2,d0 ;zs2=zd2/yd2
        move.l d0,zs2-Vars(a1)

        move.l txd2-Vars(a1),d0
        divs.l d2,d0 ;txs2=txd2/yd2
        move.l d0,txs2-Vars(a1)

        move.l tyd2-Vars(a1),d0
        divs.l d2,d0 ;tys2=tyd2/yd2
        move.l d0,tys2-Vars(a1)

        bra.s  Tdr07
Tdr06:
        move.l xd2-Vars(a1),xs2-Vars(a1)
        move.l zd2-Vars(a1),zs2-Vars(a1)
        move.l txd2-Vars(a1),txs2-Vars(a1)
        move.l tyd2-Vars(a1),tys2-Vars(a1)
Tdr07:

  or.l d3,d3     ;yd3<>0
  beq.s Tdr08
        move.l xd3-Vars(a1),d0
        divs.l d3,d0 ;xs3=xd3/yd3
        move.l d0,xs3-Vars(a1)

        move.l zd3-Vars(a1),d0
        divs.l d3,d0 ;zs3=zd3/yd3
        move.l d0,zs3-Vars(a1)

        move.l txd3-Vars(a1),d0
        divs.l d3,d0 ;txs3=txd3/yd3
        move.l d0,txs3-Vars(a1)

        move.l tyd3-Vars(a1),d0
        divs.l d3,d0 ;tys3=tyd3/yd3
        move.l d0,tys3-Vars(a1)

        bra.s  Tdr09
Tdr08:
        move.l xd3-Vars(a1),xs3-Vars(a1)
        move.l zd3-Vars(a1),zs3-Vars(a1)
        move.l txd3-Vars(a1),txs3-Vars(a1)
        move.l tyd3-Vars(a1),tys3-Vars(a1)
Tdr09:

    movem.l d0-d4,-(sp)
;   tx2=yd1*txs2
;   tx1=tbx
;   dabei links->rechts beachten
;   und beachten, daß txs2*yd1 relativ sind (keine abs. Koordinaten)

    move.l txs2-Vars(a1),d4   ;von tcx-tax
    move.l yd1-Vars(a1),d1    ;pby-pay
    muls.l d1,d4
    Round d4
    ;asr.l #8,d4      ;txw2
    add.l tax-Vars(a1),d4
    move.l tbx-Vars(a1),d0
    sub.l d4,d0

    move.l tys2-Vars(a1),d4
    muls.l d1,d4
    Round d4
    ;asr.l #8,d4      ;tyw2
    add.l tay-Vars(a1),d4
    move.l tby-Vars(a1),d3
    sub.l d4,d3

    move.l xs2-Vars(a1),d4
    muls.l d1,d4
    Round d4
    ;asr.l #8,d4      ;xw2
    add.l pax-Vars(a1),d4
    move.l pbx-Vars(a1),d2 ;d0 ist jetzt frei
    sub.l d4,d2

    bpl.s sign0
    neg.l d2
    neg.l d0
    neg.l d3
    sub.l #256,d2 ;xd etwas kleiner machen

sign0:

    or.l  d2,d2
    beq is0
    asl.l #8,d0
    asl.l #8,d3
    divs.l d2,d0  ;txd/xd=txs
    divs.l d2,d3  ;tyd/xd=tys
is0:
    ;subq.l #1,d3
    ;subq.l #1,d0
    move.l d3,tys-Vars(a1)
    move.l d0,txs-Vars(a1)
    movem.l (sp)+,d0-d4

;Stepberechnung Ende

;Triangle Hauptteil

;Startwerte
  move.l pax-Vars(a1),xw1
  move.l xw1,xw2
  move.l paz-Vars(a1),zw1
  move.l zw1,zw2
  move.l tax-Vars(a1),d0
  move.l d0,txw1-Vars(a1)
  move.l d0,txw2-Vars(a1)
  move.l tay-Vars(a1),d0
  move.l d0,tyw1-Vars(a1)
  move.l d0,tyw2-Vars(a1)

  move.l pby-Vars(a1),d0
  cmp.l pay-Vars(a1),d0
  beq   Tdr11  ;raus
;Schleifenzähler in d3
;sz equr d3   ;Änderungen für Asm-1
;cz equr d2

  move.l pay-Vars(a1),sz ;for sz:=pay to pby
  Round sz
  move.l pby-Vars(a1),cz
  Round cz

Tdr10:

        Texline

        lea txw1-Vars(a1),a0

        add.l xs1-Vars(a1),xw1
        add.l xs2-Vars(a1),xw2
        add.l zs1-Vars(a1),zw1
        add.l zs2-Vars(a1),zw2
        move.l txs1,d0
        add.l d0,(a0)+ ;txw1
        move.l txs2,d0
        add.l d0,(a0)+ ;txw2
        move.l tys1,d0
        add.l d0,(a0)+ ;tyw1
        move.l tys2,d0
        add.l d0,(a0)+ ;tyw2

        add.w #1,sz
        cmp.w  cz,sz
        ble    Tdr10

        move.l pbx-Vars(a1),xw1
        move.l pbz-Vars(a1),zw1
        move.l tbx-Vars(a1),txw1-Vars(a1)
        move.l tby-Vars(a1),tyw1-Vars(a1)
        bra.s Tdr11a

Tdr11:
  move.l pbx-Vars(a1),d0
  add.l xs3-Vars(a1),d0
  move.l d0,xw1
  move.l pbz-Vars(a1),d0
  add.l zs3-Vars(a1),d0
  move.l d0,zw1
  move.l tbx-Vars(a1),d0
  add.l txs3-Vars(a1),d0
  move.l d0,txw1-Vars(a1)
  move.l tby-Vars(a1),d0
  add.l tys3-Vars(a1),d0
  move.l d0,tyw1-Vars(a1)

Tdr11a:
  move.l pby-Vars(a1),d0
  cmp.l pcy-Vars(a1),d0
  beq   Tdr13     ;raus

  move.l pby-Vars(a1),sz ;for sz:=pay to pby
  Round sz
  add.w #1,sz    ;eine Zeile weiter im Tdreieck
  move.l pcy-Vars(a1),cz
  Round cz

Tdr12:

        Texline

        lea txw1-Vars(a1),a0

        add.l xs3-Vars(a1),xw1
        add.l xs2-Vars(a1),xw2
        add.l zs3-Vars(a1),zw1
        add.l zs2-Vars(a1),zw2
        move.l txs3-Vars(a1),d0
        add.l d0,(a0)+ ;txw1
        move.l txs2-Vars(a1),d0
        add.l d0,(a0)+ ;txw2
        move.l tys3-Vars(a1),d0
        add.l d0,(a0)+ ;tyw1
        move.l tys2-Vars(a1),d0
        add.l d0,(a0)+ ;tyw2

        add.w #1,sz
        cmp.w  cz,sz
        ble     Tdr12

Tdr13:

        movem.l (sp)+,d0-d7/a0-a6
  rts

; Übergeben: in d0 die Adresse der Struct mit den Daten
textriinit
  movem.l d0-d1/a0-a1,-(sp)

  lea Texmap,a1
  move.l d0,a0
  move.w #20-1,d1
scoploop:
  move.l (a0)+,(a1)+
  dbf d1,scoploop
  movem.l (sp)+,d0-d1/a0-a1
  rts

 cnop 0,4

vars:
TexMap dc.l $12345678
ChunkyBuf dc.l 2
FZBuf dc.l 3
CCTab dc.l 4
Tribright dc.l 5
rtax dc.l 6
rtay dc.l 7
rtbx dc.l 8
rtby dc.l 9
rtcx dc.l 10
rtcy dc.l 11

pax dc.l 12
pay dc.l 13
paz dc.l 14
pbx dc.l 15
pby dc.l 16
pbz dc.l 17
pcx dc.l 18
pcy dc.l 19
pcz dc.l 20

; def9l pax,pay,paz,pbx,pby,pbz,pcx,pcy,pcz
 def9l tax,tay,tbx,tby,tcx,tcy,zs,zd,z1

 def9l z2,xd,x1,x2,tx1,tx2,ty1,ty2,txd  ;tyd weiter oben
 def9l xd1,yd1,zd1,xd2,yd2,zd2,xd3,yd3,zd3
 def9l xs1,xs2,xs3,zs1,zs2,zs3,hx,hy,tyd
;txs = texmap-x-step innerhalb einer Zeile
;txs# = texmap-x-step bei der Dreiecksabarbeitung
 def9l txd1,tyd1,txd2,tyd2,txd3,tyd3,txs1,txs,tys
 def9l txs2,txs3,tys1,tys2,tys3,txw1,txw2,tyw1,tyw2

y dc.w 0
ctexv1
  dc.l 0,0,127<<8,0,127<<8,127<<8
ctexv2
  dc.l 0,0,127<<8,127<<8,0,127<<8
envcoords
  ds.l 3*2
checkf
  ds.l 4*2
Lightkoords
  dc.l -350<<8,-350<<8,-350<<8
Calctemp
  dc.l 0
Normaltemp
  dc.l 0,0,0
 END
