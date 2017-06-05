#define PACK_PIXEL(r, g, b) ( ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3) )
#define WIDTH 640
#define HEIGHT 480
#define SEGMENT 20

#include <kos.h>
#include <stdio.h>

int main(void) {
  int quit = 0;
  int i = 0; 
  int j = 0;

  int lastPixelWidthCase = 0;
  int lastPixelHeightCase = 0;
  int pixelWidthCase = lastPixelWidthCase;
  int pixelHeightCase = lastPixelHeightCase;
  
  //int red = 0;
  
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
    for(i = 1; i <= HEIGHT; i++){

      pixelHeightCase = i % SEGMENT;
      if(pixelHeightCase == 0){
        if(flipColor){
          flipColor = 0;
        }
        else{
          flipColor = 1;
        }
      }
      for(j = 1; j <= WIDTH; j++){
        pixel = i + (j * HEIGHT);
        pixelWidthCase = j % SEGMENT;
        if(pixelWidthCase == 0){
          if(flipColor){
            flipColor = 0;
          }
          else{
            flipColor = 1;
          }
        }
        if(flipColor) {
        	vram_s[pixel] = PACK_PIXEL(0, 0, 0);
        }
        else{
        	vram_s[pixel] = PACK_PIXEL(255, 255, 255);
        }
        
        /*
          In order to get columns take the pixel count and divide by half 
          of the width value and then mod the result by 2.  This will give
          result of 0 and 1. Where 1 is the right of the screen.

          To get rows, simply check the j value for position. If less than 
          half of y, then pixel is in top half of screen.
        */
      }
    }
  }
  return 0;
}