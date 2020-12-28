#include <gb/gb.h>
#include "UnaPack.h"

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
