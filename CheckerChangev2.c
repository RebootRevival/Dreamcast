#define PACK_PIXEL(r, g, b) ( ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3) )
#define WIDTH 640
#define HEIGHT 480
#define SEGMENT 20

#include <kos.h>
#include <stdio.h>

void setGrid(int flipColor, int pixel){
  vram_s[pixel] = flipColor ? PACK_PIXEL(0, 0, 0) : PACK_PIXEL(255, 255, 255);
}

int main(void) {
  int quit = 0;
  int i = 0; 
  int j = 0;
  maple_device_t *cont;
  cont_state_t *state;
  int a_was_down = 0;

  //init kos
  pvr_init_defaults();
 
  /*
  Set video mode
  The first is the Display Mode, which can be selected from the following:

    DM_320x240      320 x 240, 60Hz (or VGA)
    DM_640x480      640 x 480, 60Hz (or VGA)
    DM_800x608      800 x 608, 60Hz (or VGA)
    DM_256x256      256 x 256, 60Hz (or VGA)
    DM_768x480      768 x 480, 60Hz (or VGA)
    DM_768x576      768 x 576, 60Hz (or VGA)
    DM_640x480_PAL_IL 640 x 480, 50Hz
    DM_256x256_PAL_IL 256 x 256, 50Hz
    DM_768x480_PAL_IL 768 x 480, 50Hz
    DM_768x576_PAL_IL 768 x 576, 50Hz

  The second parameter selects the Pixel Mode:

    PM_RGB555 15-bit (xRRRRRGGGGGBBBBB)
    PM_RGB565 16-bit (RRRRRGGGGGGBBBBB)
    PM_RGB888 24-bit (RRRRRRRR GGGGGGGG BBBBBBBB)
  */
  vid_set_mode(DM_640x480, PM_RGB565);

  /* keep drawing frames */
  int pixel = 0;
  int flipColor =  1;
  while(!quit){
    cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER);
    if(!cont) continue;
    state = (cont_state_t *)maple_dev_status(cont);
    if(!state) continue;
    if(state->buttons & CONT_START) {
      return 0;
    }
    if(state->buttons & CONT_A) {
      if(a_was_down) continue;
      a_was_down = 1;
    }
    else {
      a_was_down = 0;
    }
    for(i = 1; i <= HEIGHT; i++){
      flipColor = !(i % SEGMENT) ? flipColor ^ 1 : flipColor;
      for(j = 1; j <= WIDTH; j++){
        pixel = i + (j * HEIGHT);
        flipColor = !(i % SEGMENT) ? flipColor ^ 1 : flipColor;
        a_was_down ? setGrid(flipColor ^ 1, pixel) : setGrid(flipColor, pixel);       
      }
    }
  }
  return 0;
}