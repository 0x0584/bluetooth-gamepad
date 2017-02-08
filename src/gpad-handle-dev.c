# include "../include/libgpad.h"


bool isbutntriggered(GPAD_DEV dev, GPAD_BUTNS butn){
  return (GPAD_STATE[dev].previous_butn & butn) == 0 &&
    (GPAD_STATE[dev].current_butn & butn) != 0; 
}

float gtrigvalue(GPAD_DEV dev, GPAD_TRIG trig) {
  return GPAD_STATE[dev].trigger[trig];
}

bool isbutndown(GPAD_DEV dev, GPAD_BUTNS butn) {
  return (GPAD_STATE[dev].current_butn & butn) != 0; 
}

bool isbutnrelzd(GPAD_DEV dev, GPAD_BUTNS butn) {
  return (GPAD_STATE[dev].previous_butn & butn) != 0 &&
  (GPAD_STATE[dev].current_butn & butn) == 0;
}

void
gstckXY(GPAD_DEV dev, GPAD_STCK stck, float *ox, float *oy)
{
  *ox = GPAD_STATE[dev].axis[stck.GPAD_WSTCK].x;
  *oy = GPAD_STATE[dev].axis[stck.GPAD_WSTCK].y;
}
 
