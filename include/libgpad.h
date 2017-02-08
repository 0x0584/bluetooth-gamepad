# ifndef GPAD_H
# define GPAD_H
/* PI */
# define PI 3.14159265358979f
# define PI_L 0.78539816339744f			/* (PI * 1/4) */
# define PI_M  0.78539816339744f		/* (PI * 1/2) */
# define PI_H 2.35619449019234f			/* (PI * 3/4) */

/* stick and trigger max value */
# define SAT_MVAL 32767.0f

/* track device connection */
# define CONNECTION_FLAG (1<<0)    

# if defined WIN32
#	include "windows.h"
#	include "xinput.h"
#	pragma comment(lib, "xinput.lib") /* ?? */
# else
#	include <unistd.h>
#	include <fcntl.h>
#	include <linux/joystick.h>
# endif	 /* WIN32 */


/* just because C has no bool-type, doesn't mean that
 * they did not think of it. but instead, you have 
 * to understand the philosophy of C in order to get
 * the idea...
 */
typedef enum BOOL {
  false = (1==0), 
  true  = !false
} bool;

/* +----------------------------------------------------+ */
/* | ------------- handle gamepad device -------------- | */
/* |							| */

/* the maximum suggested-number of gamepads that can
 * be handled is 4
 */
typedef enum GPAD_DEV {
  GPAD_1 = 0,
  GPAD_2,
  GPAD_3,
  GPAD_4,

  GPAD_COUNT			/* 4 */
} GPAD_DEV;

/* ginit - gamepad initialization
 * description: initialize the gamepad state
 * arguments: none
 * return: none
 */
void ginit(void);
void gkill(void);
void gupdate(void);
bool gisconnected(GPAD_DEV device);

/* |							| */
/* | ---------------------- END ----------------------- | */
/* +----------------------------------------------------+ */

/* +----------------------------------------------------+ */
/* | ---------- handle a particular gamepad ----------- | */
/* |							| */
/* gamepad buttons */
typedef enum GPAD_BUTNS {
  /* arrow keys */
  BUTN_UP	= (1<<0),
  BUTN_DOWN	= (1<<1),
  BUTN_LEFT	= (1<<2),
  BUTN_RIGHT	= (1<<3),

  /* start and select buttons */
  BUTN_START	= (1<<4),
  BUTN_SELECT	= (1<<5),

  /* Left and Right shoulder buttons */
  BUTN_L1	= (1<<6),
  BUTN_R1	= (1<<7),
  BUTN_L2	= (1<<8),
  BUTN_R2	= (1<<9),
  
  /* thumb buttons */
  BUTN_1	= (1<<10),
  BUTN_2	= (1<<11),
  BUTN_3	= (1<<12),
  BUTN_4	= (1<<13)
} GPAD_BUTNS;

bool isbutndown(GPAD_DEV device, GPAD_BUTNS button);
bool isbutnrelzd(GPAD_DEV device, GPAD_BUTNS button);

/* trigger */
typedef enum GPAD_TRIG { 
  TRIG_LEFT = 0, TRIG_RIGHT,
  TRIG_COUNT			/* 2 */
} GPAD_TRIG;

bool isbutntriggered(GPAD_DEV dev, GPAD_BUTNS button);
float gtrigvalue(GPAD_DEV device,
		 GPAD_TRIG trigger);

# define GPAD_STCK_L (0.35f)	/* LIGHT */
# define GPAD_STCK_M (0.60f)	/* MEDIUM */
# define GPAD_STCK_H (0.85f)	/* HEAVY */

typedef struct GPAD_STCK {
  /* Left and Right sticks (axes) */
  enum GPAD_WSTCK { 	/* which stick side is it? */
    STCK_LEFT = 0, STCK_RIGHT,
    STCK_COUNT			/* 2 */
  } GPAD_WSTCK;

  /* the four possible stick directions (UDLR) */
  enum GPAD_STCKDIREC {	/* in which direction is the stick
			 * directing to? */
    STCKDIREC_UP = 0, STCKDIREC_DOWN,
    STCKDIREC_LEFT, STCKDIREC_RIGHT
  } GPAD_STCKDIREC;
} GPAD_STCK;

void gstckXY(GPAD_DEV device,	        /* the gamepad */
	     GPAD_STCK stick,	        /* the gamepad stick */
	     float *outX, float *outY); /* coordinates of the axes 
					 * of stick  */

float gstckangle(GPAD_DEV device,	/* the gamepad  */
		 GPAD_STCK stick);	/* the stick of the gamepad */

float gstckvalue(GPAD_DEV device,	/* the gamepad  */
		 GPAD_STCK stick);	/* the stick of the gamepad */

bool gstckdir(GPAD_DEV device,		/* the gamepad */
	      GPAD_STCK stick,		/* the gamepad stick */
	      GPAD_STCK direction);	/* the stick direction */

struct GPAD_STATE {
  struct STCK_AXIS {
    float x, y,
      angle,
      value;
  } axis[STCK_COUNT];

  float trigger[TRIG_COUNT];
  int previous_butn, current_butn,
    cflag;			/* connection flag */
# if !defined WIN32
  int devfile;			/* just in case we're on a *nix OS */
# endif
} GPAD_STATE[GPAD_COUNT];
/* |							| */
/* | ---------------------- END ----------------------- | */
/* +----------------------------------------------------+ */

# endif	 /* GPAD_H */
