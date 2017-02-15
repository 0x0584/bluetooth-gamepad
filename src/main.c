/* Copyright (C) 2017 
 *				         Anas Rchid <rchid.anas@gmail.com>
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
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 ************************************************************************
 * remember this.. now you are about to create this application		* 
 * and you are motivated enough to write this, don't be superfecial	* 
 * and make this shit done at time.. you're about hell! did you know	*
 * this?? you are at the edge, be careful so that you don't fall..	*
 *									*
 * Cheers!								*
 * CHECK!								*
 ************************************************************************
 */

#include "../include/lib.h"
#include "../include/remote.h"
#include "../include/host.h"
/* #include "../include/gpad.h" */

int
main(int argc, char **argv)
{
  /* struct remote *root = init_remote(); */
  
  /* struct remote *root = NULL; */
  /* int i, responces; */
  
  /* if(argc > 2) printf("%s %s", argv[0], argv[1]); */

  /* root = (struct remote *) init_remote(&root, &responces); */

  /* for(i = 0; i < responces; ++i) */
  /*   printf("%s %s\n", root[i].addr, root[i].name); */

  struct js_event msg;
  char* device = "/dev/input/js0";
	
  int fd = open(device, O_RDONLY);
	
  while(1) {
    if(read(fd, &msg, sizeof(struct js_event)) != sizeof(struct js_event)) {
      printf("Error when reading from joystick\n");
      exit(1);
    }

    if(msg.type == JS_EVENT_BUTTON) printf("button was pressed\n");
    else if(msg.type == JS_EVENT_AXIS) printf("axis was pressed\n");	

    usleep(10000);
  }

  return EXIT_SUCCESS;
}
