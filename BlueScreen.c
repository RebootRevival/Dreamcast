#define PACK_PIXEL(r, g, b) ( ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3) )



#include <kos.h>
#include <stdio.h>

int main(void) {
  int quit = 0;
  int i = 0; 
  int j = 0;
 
  //init kos
  pvr_init_defaults();
 
  /*
  Set video mode
  The first is the Display Mode, which can be selected from the following:

    DM_320x240			320 x 240, 60Hz (or VGA)
    DM_640x480			640 x 480, 60Hz (or VGA)
    DM_800x608			800 x 608, 60Hz (or VGA)
    DM_256x256			256 x 256, 60Hz (or VGA)
    DM_768x480			768 x 480, 60Hz (or VGA)
    DM_768x576			768 x 576, 60Hz (or VGA)
    DM_640x480_PAL_IL	640 x 480, 50Hz
    DM_256x256_PAL_IL	256 x 256, 50Hz
    DM_768x480_PAL_IL	768 x 480, 50Hz
    DM_768x576_PAL_IL	768 x 576, 50Hz

  The second parameter selects the Pixel Mode:

    PM_RGB555	15-bit (xRRRRRGGGGGBBBBB)
    PM_RGB565	16-bit (RRRRRGGGGGGBBBBB)
    PM_RGB888	24-bit (RRRRRRRR GGGGGGGG BBBBBBBB)
  */
  vid_set_mode(DM_320x240, PM_RGB565);

  /* keep drawing frames */
  while(!quit){
	  for(i = 0; i < 320; i++){
	    for(j = 0; j < 240; j++){
          vram_s[i + (j * 320)] = PACK_PIXEL(0, 255, 0);  

	    }
	  }
  }

  return 0;
}