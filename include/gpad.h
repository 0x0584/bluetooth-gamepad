#ifndef GPAD_H
#define GPAD_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/joystick.h>
#include "../include/gtypes.h"

  
  struct GAMEPAD_BUTTON {
    enum BUTTON_TYPE{
      UP	= (1<<0), 
      DOWN	= (1<<1),
      LEFT	= (1<<2),
      RIGHT	= (1<<3),
      
      BUTTON_1	= (1<<4), 
      BUTTON_2	= (1<<5), 
      BUTTON_3	= (1<<6), 
      BUTTON_4	= (1<<7),

      BUTTON_L1	= (1<<8), 
      BUTTON_R1	= (1<<9), 
      BUTTON_L2	= (1<<10), 
      BUTTON_R2	= (1<<11),

      BUTTON_SELECT = (1<<12),
      BUTTON_START  = (1<<13),
    } previous, current;
  };

  struct GAMEPAD_AXE {
    float x, y,
      angle, value;
  };

  struct GAMEPAD_INFO {
    unsigned short id,
      naxes, nbuttons;
    char *name, *path;
    int fd;
  };
  
  extern struct GAMEPAD {
    gpad_info *info;
    gpad_axe *axes;
    gpad_butn *buttons;

    struct js_event *jse;
  } *master;

  gpad_t *ginit();
  void ginfo(gpad_t *);
  void gevent(struct js_event *jse);
  void gkill(gpad_t *);

#ifdef __cplusplus
}
#endif
#endif
