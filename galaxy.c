#include <gb/gb.h>
#include "UnaPack.h"

#define SET_RAM_MBC1_MODE(b) \
  *(unsigned char *)0x6000 = (b)

// current_bank contains the bank and it's type ROM or RAM
volatile __sfr __at (0xFC) __current_ram_bank;
volatile __sfr __at (0xFD) __current_rom_bank;
#define SET_ROM_BANK(n) ((__current_rom_bank = (n)), SWITCH_ROM_MBC1((n)))
#define SET_RAM_BANK(n) ((__current_ram_bank = (n)), SWITCH_RAM_MBC1((n)))
#define SET_BANKS(rom, ram) \
  (SET_ROM_BANK((rom)), SET_RAM_BANK((ram)))
#define RESTORE_BANKS \
  (SWITCH_ROM_MBC1(__current_rom_bank), SWITCH_RAM_MBC1(__current_ram_bank))

// force bank switching macro
volatile __sfr __at (0xFE) __dummy_variable;
#define switch_to(x) (__dummy_variable = (char)((x)[0]), (void *)(x))

void set_ROM_bank1(void) NONBANKED __preserves_regs(b, c, d, e) { SET_ROM_BANK(1); }
void set_ROM_bank2(void) NONBANKED __preserves_regs(b, c, d, e) { SET_ROM_BANK(2); }
void set_ROM_bank3(void) NONBANKED __preserves_regs(b, c, d, e) { SET_ROM_BANK(3); }
void set_ROM_bank4(void) NONBANKED __preserves_regs(b, c, d, e) { SET_ROM_BANK(4); }
void set_ROM_bank5(void) NONBANKED __preserves_regs(b, c, d, e) { SET_ROM_BANK(5); }
void set_ROM_bank6(void) NONBANKED __preserves_regs(b, c, d, e) { SET_ROM_BANK(6); }
void set_ROM_bank7(void) NONBANKED __preserves_regs(b, c, d, e) { SET_ROM_BANK(7); }
void set_ROM_bank8(void) NONBANKED __preserves_regs(b, c, d, e) { SET_ROM_BANK(8); }
void set_ROM_bank9(void) NONBANKED __preserves_regs(b, c, d, e) { SET_ROM_BANK(9); }
void set_ROM_bank10(void) NONBANKED __preserves_regs(b, c, d, e) { SET_ROM_BANK(10); }
void set_ROM_bank11(void) NONBANKED __preserves_regs(b, c, d, e) { SET_ROM_BANK(11); }
void set_ROM_bank12(void) NONBANKED __preserves_regs(b, c, d, e) { SET_ROM_BANK(12); }
void set_ROM_bank13(void) NONBANKED __preserves_regs(b, c, d, e) { SET_ROM_BANK(13); }
void set_ROM_bank14(void) NONBANKED __preserves_regs(b, c, d, e) { SET_ROM_BANK(14); }
void set_ROM_bank15(void) NONBANKED __preserves_regs(b, c, d, e) { SET_ROM_BANK(15); }
void set_ROM_bank16(void) NONBANKED __preserves_regs(b, c, d, e) { SET_ROM_BANK(16); }
void set_ROM_bank17(void) NONBANKED __preserves_regs(b, c, d, e) { SET_ROM_BANK(17); }
void set_ROM_bank18(void) NONBANKED __preserves_regs(b, c, d, e) { SET_ROM_BANK(18); }

__addressmod set_ROM_bank1 const CODE_1;
__addressmod set_ROM_bank2 const CODE_2;
__addressmod set_ROM_bank3 const CODE_3;
__addressmod set_ROM_bank4 const CODE_4;
__addressmod set_ROM_bank5 const CODE_5;
__addressmod set_ROM_bank6 const CODE_6;
__addressmod set_ROM_bank7 const CODE_7;
__addressmod set_ROM_bank8 const CODE_8;
__addressmod set_ROM_bank9 const CODE_9;
__addressmod set_ROM_bank10 const CODE_10;
__addressmod set_ROM_bank11 const CODE_11;
__addressmod set_ROM_bank12 const CODE_12;
__addressmod set_ROM_bank13 const CODE_13;
__addressmod set_ROM_bank14 const CODE_14;
__addressmod set_ROM_bank15 const CODE_15;
__addressmod set_ROM_bank16 const CODE_16;
__addressmod set_ROM_bank17 const CODE_17;
__addressmod set_ROM_bank18 const CODE_18;

#include "song.h"

const unsigned char gb_data[] = {
#include "gb2_chr.h"
};

const unsigned char gb_map[] = {
#include "gb2_map.h"
};

static UBYTE time = 0;

void main()
{
  disable_interrupts();
  DISPLAY_OFF;

  LCDC_REG = 0x9;
  BGP_REG = OBP0_REG = OBP1_REG = 0x1B;

  set_bkg_data(0x00, 244, gb_data);
  set_bkg_tiles(0, 0, 20, 18, gb_map);

  SCX_REG = 0;
  SCY_REG = 0;

  DISPLAY_ON;
  enable_interrupts();

  while(1) {
    wait_vbl_done();
    time++;
  }

}
