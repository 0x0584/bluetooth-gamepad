/*
 *  Copyright (C) 2017 Anas Rchid
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or 
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * Should you need to contact me, the author, you can do so either by
 * e-mail - mail your message to <rchid.anas@gmail.com>.
 */

#ifndef GPAD_H
#define GPAD_H
#define PI  3.14159265358979f
#define PI_L 0.78539816339744f		/* (PI * 1/4) */
#define PI_M  0.78539816339744f		/* (PI * 1/2) */
#define PI_H 2.35619449019234f		/* (PI * 3/4) */

/* track device connectivity */
#define CONNECTION_FLAG (1<<0)    

#if defined WIN32
# include "windows.h"
# include "xinput.h"
#else
# include <unistd.h>	/* close */
# include <fcntl.h>	/* open */
# include <linux/joystick.h>
#endif	 /* WIN32 */

/* stick and trigger max value */
#define SAT_MVAL  32767.0f

/* gamepad-stick sensitivity */
#define SS_LIGHT (0.35f)	/* LIGHT */
#define SS_MEDIUM (0.60f)	/* MEDIUM */
#define SS_HEAVY (0.85f)	/* HEAVY */

/* just because C has no bool-type, doesn't mean that
 * they did not think of it. but instead, you have 
 * to understand the philosophy of C in order to get
 * the idea...
 */
typedef enum ENUM_BOOL_TYPE {
  false = (1==0), 
  true  = !false
} bool;

/* defining STRUCT_GAMEPAD as GPAD type */
typedef struct STRUCT_GAMEPAD GPAD;

/* prototype of `gpad_process` type (void function which
 * recieve no-arguments) */
typedef void gpad_process(void);

/* prototype of `gpad_behavior` (functions which recieve
 * a GPAD as argument && return bool) */
typedef bool gpad_behavior(GPAD);


extern struct STRUCT_GAMEPAD {
  /* connection flag */
  int cflag;

#if !defined WIN32
  /* declare `file descriptor` in case if
   * we were in a *nix OS */
  int fd;
#endif
  
  /* the maximum suggested-number of gamepads that can
   * be handled is 4 */
  enum ENUM_GAMEPAD_DEVICE {
    GPAD_1 = 0,
    GPAD_2,
    GPAD_3,
    GPAD_4,

    GPAD_COUNT				/* 4 */
  } DEVICE;

  /* gamepad behavior */
  struct STRUCT_GAMEPAD_BEHAVIOR {
    /* gamepad buttons */
    struct STRUCT_GAMEPAD_BUTTON{
      /* button type */
      enum ENUM_GAMEPAD_BUTTON_TYPE {
	/* arrow keys */
	BUTN_UP		= (1<<0),
	BUTN_DOWN	= (1<<1),
	BUTN_LEFT	= (1<<2),
	BUTN_RIGHT	= (1<<3),

	/* start/select buttons */
	BUTN_START	= (1<<4),
	BUTN_SELECT	= (1<<5),

	/* shoulder-buttons */
	BUTN_L1		= (1<<6),
	BUTN_R1		= (1<<7),
	BUTN_L2		= (1<<8),
	BUTN_R2		= (1<<9),
  
	/* thumb-buttons */
	BUTN_1		= (1<<10),
	BUTN_2		= (1<<11),
	BUTN_3		= (1<<12),
	BUTN_4		= (1<<13)
      } BUTN_TYPE;
  
      /* button trigger */
      enum ENUM_GAMEPAD_BUTTON_TRIGGER { 
	TRIG_LEFT = 0, TRIG_RIGHT,
	TRIG_COUNT			/* 2 */
      } BUTN_TRIG;
      
      float trigger[TRIG_COUNT];
      int previous_butn, current_butn;
    } BUTTON;

    /* gamepad stick */
    struct STRUCT_GAMEPAD_STICK {
      /* (which stick-side (LR axes) */
      enum ENUM_GAMEPAD_WHICH_STCK {
	STCK_LEFT = 0, STCK_RIGHT,
	STCK_COUNT			/* 2 */
      } WSTCK;

      /* the four possible stick directions (UDLR) */
      enum ENUM_GAMEPAD_STICK_DIRECTION {
	STCKDIREC_UP = 0, STCKDIREC_DOWN,
	STCKDIREC_LEFT, STCKDIREC_RIGHT
      } STCKDIREC;

      /* gamepad stick-axis */
      struct STRUCT_GAMEPAD_STICK_AXIS {
	float x, y,
	  angle, value;
      } AXIS;
    } STICK[STCK_COUNT];
  } BEHAVIOR;
} GDEV[GPAD_COUNT];

/* gamepad-related processing */
gpad_process ginit, gkill, gupdate;

/* handle gamepad */
gpad_behavior gisconnected,
  isbutndown, isbutnrelzd, isbutntriggered, gtrigvalue,
  gstckangle, gstckvalue, gstckdirec;

#endif	 /* GPAD_H */
