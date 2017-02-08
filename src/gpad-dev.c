# include <math.h>
# include <string.h>
# include <stdio.h>
# include "../include/libgpad.h"

void
ginit(void)
{
  memset(GPAD_STATE, 0, sizeof(GPAD_STATE));

# if !defined WIN32
# define N_DEVICES 128  
  int i;			/* the counter */

  /* loop throw the gamepads */
  for(i = 0; i < GPAD_COUNT; ++i) {
    char buffer[N_DEVICES];    

    /* getting the path of the `device file` */
    snprintf(buffer, N_DEVICES, "/dev/input/js%d", i);

    /* openining the `device file` and setting the connection flag */
    if((GPAD_STATE[i].devfile = open(buffer, O_RDONLY | O_NONBLOCK)) != -1)
      GPAD_STATE[i].cflag |= CONNECTION_FLAG;
  }
# endif
}

void
gkill(void)
{
# if !defined WIN32
  int i;

  /* closing the which are not connected */
  for(i = 0; i < GPAD_COUNT; ++i)
    if(GPAD_STATE[i].devfile != -1)
      close(GPAD_STATE[i].devfile);
# endif
}

void
gupdate(void)
{
  int i;
  
  for(i = 0; i < GPAD_COUNT; ++i) {
# if defined WIN32
    XIPNUT_STATE xin_state;

    /* updating the gamepad state */
    if(!XInputGetState(i, &xin_state)) {
      float ttrigger;

      /* setting the trigger value */
      ttrigger[TRIG_LEFT] = = xin_state.Gamepad.bLeftTrigger / 255.f;
      ttrigger[TRIG_LEFT] = = xin_state.Gamepad.bRightTrigger / 255.f;
      GPAD_STATE[i].trigger = ttrigger;
      
      /* set the connection flag */
      GPAD_STATE[i].cflag |= CONNECTION_FLAG;

      /* setting the current button state */
      GPAD_STATE[i].current_butn = xin_state.Gamepad.wButtons;

      /* setting the axis state */
      GPAD_STATE[i].axis[STICK_LEFT].x = xin_state.Gamepad.sThumbLX / SAT_MVAL;
      GPAD_STATE[i].axis[STICK_LEFT].y = xin_state.Gamepad.sThumbLY / SAT_MVAL;
      GPAD_STATE[i].axis[STICK_RIGHT].x = xin_state.Gamepad.sThumbRX / SAT_MVAL;
      GPAD_STATE[i].axis[STICK_RIGHT].x = xin_state.Gamepad.sThumbRY / SAT_MVAL;      
    }
    else {
      GPAD_STATE[i].cflag ^= CONNECTION_FLAG;
    }
# else
    if(GPAD_STATE[i].devfile != -1) {
      struct js_event jsevent;
    
      while(read(GPAD_STATE[i].devfile, &jsevent, sizeof(jsevent) > 0)) {
	int butn;

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

	  if(jsevent.value) GPAD_STATE[i].current_butn |= butn;
	  else GPAD_STATE[i].current_butn ^= butn;
	  break;
	  
	case JS_EVENT_AXIS:
	  switch(jsevent.number) {
	  case 0: GPAD_STATE[i].axis[STCK_LEFT].x = jsevent.value / SAT_MVAL;
	  case 1: GPAD_STATE[i].axis[STCK_LEFT].y = jsevent.value / SAT_MVAL;
	  case 2: GPAD_STATE[i].trigger[TRIG_LEFT] = jsevent.value / SAT_MVAL;

	  case 3: GPAD_STATE[i].axis[STCK_LEFT].x = jsevent.value / SAT_MVAL;
	  case 4: GPAD_STATE[i].axis[STCK_LEFT].x = jsevent.value / SAT_MVAL;
	  case 5: GPAD_STATE[i].trigger[TRIG_LEFT] = jsevent.value / SAT_MVAL;
	  default: break;
	  }
	  break;

	default: break;		/* !JS_EVENT_BUTTON || !JS_EVENT_AXIS */
	} 
      }
    }
# endif

    /* updating the stick angles and magnitudes */
    if((GPAD_STATE[i].cflag & CONNECTION_FLAG) != 0) {
      float tsqrt,		/* a temporary square-root holder  */
	tatan;			/* a temporary arc-tangent holder */

      /* left stick */
      tsqrt = sqrtf(powf(GPAD_STATE[i].axis[STCK_LEFT].x, 2)
		    + powf(GPAD_STATE[i].axis[STCK_LEFT].y, 2));
      tatan = atan2f(GPAD_STATE[i].axis[STCK_LEFT].y,
		     GPAD_STATE[i].axis[STCK_LEFT].x);

      GPAD_STATE[i].axis[STCK_LEFT].value = tsqrt;
      GPAD_STATE[i].axis[STCK_LEFT].angle = tatan;

      /* right stick */
      tsqrt = sqrtf(powf(GPAD_STATE[i].axis[STCK_RIGHT].x, 2)
		    + powf(GPAD_STATE[i].axis[STCK_RIGHT].y, 2));
      tatan = atan2f(GPAD_STATE[i].axis[STCK_RIGHT].y,
		     GPAD_STATE[i].axis[STCK_RIGHT].x);
      
      GPAD_STATE[i].axis[STCK_RIGHT].value = tsqrt;
      GPAD_STATE[i].axis[STCK_RIGHT].angle = tatan;
    }
  }
}
    
bool gisconnected(GPAD_DEV dev) {
  return GPAD_STATE[dev].cflag & CONNECTION_FLAG;
}
