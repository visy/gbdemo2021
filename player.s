.area _BSS

Song:
    .ds  1
CurrentBank:
    .ds  2
CurrentPtr:
    .ds  2

.area _CODE

; Starts playing a song. If a song is already playing,
; make sure interrupts are disabled when calling this.
;
; IN: a = song number
; OUT: -
; SIDE EFFECTS: trashes af
;
LsdjPlaySong:
    push    de
    push    hl

    ld  (Song),a
    ld  d,#0
    add a,a
    add a,a
    ld  e,a

    ld  hl, #1
    add hl,de

    ld  a,(hl+)
    ld  (CurrentBank),a
    ld  a,(hl+)
    ld  (CurrentBank+1),a
    ld  a,(hl+)
    ld  (CurrentPtr),a
    ld  a,(hl)
    ld  (CurrentPtr+1),a

    pop hl
    pop de
    ret

; Call this six times per screen update,
; evenly spread out over the screen.
;
; IN: -
; OUT: -
; SIDE EFFECTS: changes ROM bank, trashes af
;
LsdjTick:
    push    bc
    push    de
    push    hl

.tick:
    ld  a,(CurrentBank+1)
    ld  (0x3000),a
    ld  a,(CurrentBank)
    ld  (0x2000),a
    ld  a,(CurrentPtr+1) ; hl = ptr
    ld  h,a
    ld  a,(CurrentPtr)
    ld  l,a

    ld  d,#0xff

.loop:
    ld  a,(hl+)
    or  a
    jr  z,.lyc_done
    cp  #1
    jr  z,.handle_sample
    cp  #2
    jr  z,.handle_stop
    cp  #3
    jp  z,.next_bank

    ; write sound register
    ld  b,a
    and #0x7f
    ld  e,a
    ld  a,(hl+)
    ld  (de),a
    ld  a,b
    bit 7,a ; test LYC_END
    jr  z,.loop

.lyc_done:
    ld  a,l
    ld  (CurrentPtr),a
    ld  a,h
    ld  (CurrentPtr+1),a
    pop hl
    pop de
    pop bc
    ret

.handle_stop:
    ld  a,(Song)
    call    LsdjPlaySong
    jr  .tick

.handle_sample:
    ld  a,(hl+)
    ld  b,a     ; b = sample bank
    ld  a,(hl+)
    ld  e,a
    ld  a,(hl+)
    ld  d,a     ; de = sample ptr

    push    hl
    ; switch bank
    xor a
    ld  (0x3000),a
    ld  a,b
    ld  (0x2000),a

    ld  h,d
    ld  l,e

    ; disable wave channel output
    ldh a,(0x25)
    ld  e,a
    and a,#0xbb
    ldh (0x25),a

    xor a
    ldh (0x1a),a ; mute channel

    ld  a,(hl+)
    ldh (0x30),a
    ld  a,(hl+)
    ldh (0x31),a
    ld  a,(hl+)
    ldh (0x32),a
    ld  a,(hl+)
    ldh (0x33),a
    ld  a,(hl+)
    ldh (0x34),a
    ld  a,(hl+)
    ldh (0x35),a
    ld  a,(hl+)
    ldh (0x36),a
    ld  a,(hl+)
    ldh (0x37),a
    ld  a,(hl+)
    ldh (0x38),a
    ld  a,(hl+)
    ldh (0x39),a
    ld  a,(hl+)
    ldh (0x3a),a
    ld  a,(hl+)
    ldh (0x3b),a
    ld  a,(hl+)
    ldh (0x3c),a
    ld  a,(hl+)
    ldh (0x3d),a
    ld  a,(hl+)
    ldh (0x3e),a
    ld  a,(hl+)
    ldh (0x3f),a

    ld  a,#0x80 ; unmute
    ldh (0x1a),a

    pop     hl

    ld  a,(CurrentBank)
    ld  (0x2000),a
    ld  a,(CurrentBank+1)
    ld  (0x3000),a

    ld  a,(hl+)
    ldh (0x1e),a
    ld  a,(hl+)
    ldh (0x1d),a

    ld  a,e
    ldh (0x25),a

    ld  d,#0xff
    jp  .loop

.next_bank:
    ld  a,#0x40
    ld  h,a
    xor a
    ld  l,a

    ld  a,(CurrentBank)
    inc a
    ld  (CurrentBank),a
    ld  (0x2000),a
    jp  nz,.loop
    ld  a,(CurrentBank+1)
    inc a
    ld  (CurrentBank+1),a
    ld  (0x3000),a
    jp  .loop
