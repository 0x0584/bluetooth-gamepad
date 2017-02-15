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

  /* gamepad types */
#include "../include/gtypes.h"

  struct GAMEPAD_BUTTON {
    enum BUTTON_TYPE{
      UP = 0, DOWN, 
      LEFT, RIGHT,
      
      BUTTON_1, BUTTON_2,
      BUTTON_3, BUTTON_4,

      BUTTON_L1, BUTTON_R1,
      BUTTON_L2, BUTTON_R2,

      BUTTON_SELECT,
      BUTTON_START,

      BUTTON_COUNT
    } previous, current;
  };

  struct GAMEPAD_AXE {
    float x, y,
      angle, value;
  };

  struct GAMEPAD_STICK {
    enum STICK_SIDE {
      STCK_LEFT = 0, S_RIGHT,
      STCK_COUNT
    } side;

    enum DIRECTION {
      SDIREC_CENTER = 0,
      SDIREC_LEFT,
      SDIREC_RIGHT,
      SDIREC_UP,
      SDIREC_DOWN,
      
      SD_COUNT
    }direc;
  };
  struct GAMEPAD_INFO {
    unsigned short id,
      naxes, nbuttons;
    char *name, *path;
    int fd;

    bool isconnected;
  };
  
  extern struct GAMEPAD {
    gpad_info *info;
    gpad_axe *axes;
    gpad_butn *buttons;

    struct js_event *e;
  } *master;

  gpad_t *ginit();
  gpad_t *ginfo(gpad_t *);
  void gevent(struct js_event *jse);
  void gkill(gpad_t *);

#ifdef __cplusplus
}
#endif
#endif
