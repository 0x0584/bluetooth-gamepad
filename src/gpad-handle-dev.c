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

#include "../include/libgpad.h"


bool isbutntriggered(GPAD gamepad){
  return (gamepad.previous_butn & butn) == 0 &&
    (gamepad.current_butn & butn) != 0; 
}

float gtrigvalue(GPAD gamepad) {
  return gamepad.trigger[trig];
}

bool isbutndown(GPAD_DEV dev, GPAD_BUTN butn) {
  return (GPAD_STATE[dev].current_butn & butn) != 0; 
}

bool isbutnrelzd(GPAD_DEV dev, GPAD_BUTN butn) {
  return (GPAD_STATE[dev].previous_butn & butn) != 0 &&
  (GPAD_STATE[dev].current_butn & butn) == 0;
}

void
gstckXY(GPAD_DEV dev, GPAD_STCK stck, float *ox, float *oy)
{
  *ox = GPAD_STATE[dev].axis[stck.GPAD_WSTCK].x;
  *oy = GPAD_STATE[dev].axis[stck.GPAD_WSTCK].y;
}

float gstckvaluealue(GPAD_DEV dev, GPAD_STCK stck) {
  return GPAD_STATE[dev].axis[stck.GPAD_WSTCK].value;
}

float gstckangle(GPAD_DEV dev, GPAD_STCK stck) {
  return GPAD_STATE[dev].axis[stck.GPAD_WSTCK].angle;
}

bool gstckdirec(GPAD_DEV dev, GPAD_STCK stck) {
  if (GPAD_STATE[dev].axis[stck.GPAD_WSTCK].value < GPAD_STCK_L)
    return false;

  float tangle = GPAD_STATE[dev].axis[stck.GPAD_WSTCK].angle;
  
  switch (stck.GPAD_STCKDIREC) {
  case STCKDIREC_LEFT: return tangle >= PI_H && tangle < -PI_H;
  case STCKDIREC_RIGHT: return tangle < PI_L && tangle >= -PI_L;
  case STCKDIREC_UP: return tangle >= PI_L && tangle < PI_H;
  case STCKDIREC_DOWN: return tangle >= -PI_H && tangle < -PI_L;
  default: return false;
  }
}
