#include <stdio.h>		/* printf */
#include <stdlib.h>		/* exit */
#include <unistd.h>		/* usleep */
#include <fcntl.h>   		/* open */
#include <linux/joystick.h>	/* js_event */

int
main()
{
  struct js_event msg;
  char* device = "/dev/input/js0";
	
  int fd = open(device, O_RDONLY);
	
  while(1) {
    if(read(fd, &msg, sizeof(struct js_event)) != sizeof(struct js_event)) {
      printf("Error when reading from joystick\n");
      exit(1);
    } else {
      if(msg.type == JS_EVENT_BUTTON) 
	printf("button press\n");
      if(msg.type == JS_EVENT_AXIS)
	printf("axis pressed\n");	
      usleep(10000);
    }
  }
	
  return 0;
}
