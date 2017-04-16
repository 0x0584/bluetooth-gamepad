#include "../include/gpad.h"

void
gevent(gpad_t *dev)
{
  if(isnull(dev)) goto FAIL;

#if defined DEBUG
  printf("type:%u\tvalue:%u\tnumber:%u\ttime%u\n",
	 dev->e->type, dev->e->value, dev->e->number, dev->e->time);
#endif

  int rd;
  int button;

  char *buttons[] = {"1", "2", "3", "4",
		     "L1", "R1",
		     "SELECT","START",
		     "SP"
		     "L2", "R2"};
  
  while((rd = read(dev->info->fd, dev->e, sizeof(struct js_event)))) {
    if(rd != sizeof(struct js_event)) goto HERE;
    
    switch(dev->e->type){
    case JS_EVENT_BUTTON: 

      switch (dev->e->number) {
      case 0: button = BUTTON_1; break;
      case 1: button = BUTTON_2; break;
      case 2: button = BUTTON_3; break;
      case 3: button = BUTTON_4; break;
	  
      case 4: button = BUTTON_L1; break;
      case 5: button = BUTTON_R1; break;
	  
      case 6: button = BUTTON_SELECT; break;
      case 7: button = BUTTON_START; break;

      case 8: button = 0; break; /* sp_button  */

      case 9: button = BUTTON_L2; break;
      case 10: button = BUTTON_R2; break;
	  
      default: button = 0; break;
      }

      /* set or unset the button */
      if (dev->e->value) dev->state->button->current |= button;
      else dev->state->button->current ^= button;
					
      printf("buttons pressed%s\n", buttons[button]);
      break;

    case JS_EVENT_AXIS: 
      printf("axis pressed\n");
      break;

    default:
      printf(".");
      break;
    }

  HERE:
    usleep(10000);
    continue;
  }

 FAIL:
  return;
}
