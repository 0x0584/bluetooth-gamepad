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

  /* max # of supported devices */
#define MAX_SUPPORTED (1<<4)
  
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

    enum STICK_DIRECTION {
      STCKDIREC_CENTER = 0,
      STCKDIREC_LEFT,
      STCKDIREC_RIGHT,
      STCKDIREC_UP,
      STCKDIREC_DOWN,
      
      STCKDIREC_COUNT
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

    struct GAMEPAD_STATE {
      gpad_axe *axe;
      gpad_butn *button;
      gpad_stck *stick;
    } *state;
    
    struct js_event *e;
  } *master;

  gpad_t *ginit();
  gpad_t *ginfo(gpad_t *);
  void gkill(gpad_t *);

  void gevent(gpad_t *);

#ifdef __cplusplus
}
#endif
#endif
