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

#include <math.h>
#include <string.h>		/* memeset,  */
#include <stdio.h>		/* snprintf, */
#include "../include/libgpad.h"

void
ginit(void)
{
  /* initialize the gamepads state with */
  memset(GDEV, (unsigned char) 0x00, (GPAD_COUNT * sizeof(GPAD)));

#if defined WIN32
  /* the xinput library take care of this */
#else
  int i;			/* our counter */

  /* loop throw all the gamepads and set their connection-flag */
  for(i = 0; i < GPAD_COUNT; ++i) {
    char buffer[128];

    /* getting the path of the gamepad `file descriptor` */
    snprintf(buffer, sizeof(buffer), "/dev/input/js%d", i);

    /* opening the gamepad `file descriptor` */
    if((GDEV[i].fd = open(buffer, O_RDONLY | O_NONBLOCK)) != -1)
      /* the gamepad is existed; set its connection-flag */
      GDEV[i].cflag |= CONNECTION_FLAG;
  }
#endif
}

void
foo(void)
{
#if defined WIN32
  /* there's no device-file in windows..*/
#else
  int i;

  /* closing the existed gamepads connected */
  for(i = 0; i < GPAD_COUNT; ++i)
    if(GDEV[i].fd != -1)
      /* kill the active gamepad file descriptor */
      close(GDEV[i].fd);
#endif
}


void
gupdate(void)
{
  int i;

  for(i = 0; i < GPAD_COUNT; ++i) {
#if defined WIN32
    XIPNUT_STATE xin_state;

    /* updating the state of the connected gamepads */
    if(!XInputGetState(i, &xin_state)) {
      float fvar;

      /* setting the left-trigger value */
      fvar = xin_state.Gamepad.bLeffvar / 255.f;
      GDEV[i].GPAD_BUTN.trigger[TRIG_LEFT] = fvar;

      /* setting the right-trigger value */
      fvar = xin_state.Gamepad.bRighfvar / 255.f;
      GDEV[i].GPAD_BUTN.trigger[TRIG_RIGHT] = fvar;
      
      /* set the connection-flag */
      GDEV[i].cflag |= CONNECTION_FLAG;

      /* setting the current-button state */
      GDEV[i].GPAD_BUTN.current_butn = xin_state.Gamepad.wButtons;

      /* setting the gamepad-axis state */
      fvar = xin_state.Gamepad.sThumbLX / SAT_MVAL;
      GDEV[i].GPAD_STCK[STICK_LEFT].AXIS.x = fvar;

      fvar = xin_state.Gamepad.sThumbLY / SAT_MVAL;
      GDEV[i].GPAD_STCK[STICK_LEFT].AXIS.y = fvar;

      fvar = xin_state.Gamepad.sThumbRX / SAT_MVAL;
      GDEV[i].GPAD_STCK[STICK_RIGHT].AXIS.x = fvar;
      
      fvar = xin_state.Gamepad.sThumbRY / SAT_MVAL;      
      GDEV[i].GPAD_STCK[STICK_RIGHT].AXIS.y = fvar;
    }
    /* the gamepad is not connected */
    else GDEV[i].cflag ^= CONNECTION_FLAG;
#else
    if(GDEV[i].fd != -1) {
      struct js_event jsevent;
    
      while(read(GDEV[i].fd, &jsevent, sizeof(jsevent) > 0)) {
	int butn;
	float temp;
	
	switch(jsevent.type){
	case JS_EVENT_BUTTON:
	  switch (jsevent.number) {
	    /* in case it's a thumb button */
	  case 0: butn = BUTN_1; break;
	  case 1: butn = BUTN_2; break;
	  case 2: butn = BUTN_3; break;
	  case 3: butn = BUTN_4; break;

	    /* L1 and R1 buttons */
	  case 4: butn = BUTN_L1; break;
	  case 5: butn = BUTN_R1; break;

	    /* select and start buttons */
	  case 6: butn = BUTN_SELECT; break;
	  case 7: butn = BUTN_START; break;

	    /* XBOX button */
	  case 8: butn = 0; break;

	    /* L2 and R2 buttons */
	  case 9: butn = BUTN_L2; break;
	  case 10: butn = BUTN_R2; break;

	    /* any additional (non-standard) buttons */
	  default: butn = 0;
	  }

	  if(jsevent.value) GDEV[i].BEHAVIOR.BUTTON.current_butn |= butn;
	  else GDEV[i].BEHAVIOR.BUTTON.current_butn ^= butn;
	  break;			/* JS_EVENT_BUTTON */
	  
	case JS_EVENT_AXIS:
	  temp = jsevent.value / SAT_MVAL;
	  
	  switch(jsevent.number) {
	  case 0: GDEV[i].BEHAVIOR.STICK[STCK_LEFT].AXIS.x = temp;
	  case 1: GDEV[i].BEHAVIOR.STICK[STCK_LEFT].AXIS.y = temp;
	  case 2: GDEV[i].BEHAVIOR.BUTTON.trigger[TRIG_LEFT] = temp;

	  case 3: GDEV[i].BEHAVIOR.STICK[STCK_RIGHT].AXIS.x = temp;
	  case 4: GDEV[i].BEHAVIOR.STICK[STCK_RIGHT].AXIS.y = temp;
	  case 5: GDEV[i].BEHAVIOR.BUTTON.trigger[TRIG_RIGHT] = temp;
	  default: break;
	  }
	  break;			/* JS_EVENT_AXIS */

	default: break;			/* !JS_EVENT_BUTTON || !JS_EVENT_AXIS */
	} 
      }
    }
#endif

    /* updating the stick angles and magnitudes */
    if((GDEV[i].cflag & CONNECTION_FLAG) != 0) {
      float tsqrt,		/* a temporary square-root holder  */
	tatan;			/* a temporary arc-tangent holder */

      /* left gamepad-stick */
      tsqrt = sqrtf(powf(GDEV[i].BEHAVIOR.STICK[STCK_RIGHT].AXIS.x, 2)
		    + powf(GDEV[i].BEHAVIOR.STICK[STCK_RIGHT].AXIS.y, 2));
      tatan = atan2f(GDEV[i].BEHAVIOR.STICK[STCK_RIGHT].AXIS.y,
		     GDEV[i].BEHAVIOR.STICK[STCK_RIGHT].AXIS.x);

      GDEV[i].BEHAVIOR.STICK[STCK_RIGHT].AXIS.value = tsqrt;
      GDEV[i].BEHAVIOR.STICK[STCK_RIGHT].AXIS.angle = tatan;

      /* right gamepad-stick */
      tsqrt = sqrtf(powf(GDEV[i].BEHAVIOR.STICK[STCK_RIGHT].AXIS.x, 2)
		    + powf(GDEV[i].BEHAVIOR.STICK[STCK_RIGHT].AXIS.y, 2));
      tatan = atan2f(GDEV[i].BEHAVIOR.STICK[STCK_RIGHT].AXIS.y,
		     GDEV[i].BEHAVIOR.STICK[STCK_RIGHT].AXIS.x);
      
      GDEV[i].BEHAVIOR.STICK[STCK_RIGHT].AXIS.value = tsqrt;
      GDEV[i].BEHAVIOR.STICK[STCK_RIGHT].AXIS.angle = tatan;
    }
  }
}
    
bool gisconnected(GPAD gamepad) {
  return gamepad.cflag & CONNECTION_FLAG;
}
