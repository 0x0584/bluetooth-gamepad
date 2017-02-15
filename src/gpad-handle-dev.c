#include "../include/gpad.h"

void
gevent(struct js_event *jse)
{

  printf("jse: %d\n", jse->type);
  getchar();
  
  /* if (jse->type == 2) { */
  /*   if (jse->number == 0) { */
  /*     if (jse->value < 0) { */
  /* 	printf("LEFT\n"); */
  /*     } else if (jse->value > 0) { */
  /* 	printf("RIGHT\n"); */
  /*     } */
  /*   } else { */
  /*     if (jse->value < 0) { */
  /* 	printf("UP\n"); */
  /*     } else if (jse->value > 0) { */
  /* 	printf("DOWN\n"); */
  /*     } */
  /*   } */

  /*   if (jse->type == 1 && jse->value > 0) { */
  /*     printf("%d\n", jse->number); */
  /*   } */
  /* } */

  switch(jse->type){
  case JS_EVENT_BUTTON: printf("buttons pressed");
    break;
  case JS_EVENT_AXIS: printf("axispressed");
    break;
  default: puts("not an event!");
  }
}
