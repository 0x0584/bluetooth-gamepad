/* License: GPL v2
 *
 * Copyright (C) 2017 Anas Rchid <rchid.anas@gmail.com>
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
 ************************************************************************
 */

# include <errno.h>  /* ensure you understand this library this time.. */
# include <stdio.h> 
# include <stdlib.h>
# include <unistd.h>
# include <sys/socket.h>

/* Bluez bluetooth libraries */
# include <bluetooth/bluetooth.h>
# include <bluetooth/hci.h>
# include <bluetooth/hci_lib.h>
# include <bluetooth/rfcomm.h>

# define MAX_RESPONSES 255	/* pow(2, 8) */
# define NAME_SIZE 248
# define ADDRESS_SIZE 19

# pragma pack(push)  /* push current alignment to stack */
# pragma pack(1)     /* set alignment to 1 byte boundary */
struct host{
  int device_id, socket, length;
  long flags;
};
# pragma pack(pop) /* restore original alignment from stack */

/* struct(s) */
struct remote{
  char name[NAME_SIZE],
    addr[ADDRESS_SIZE];
};

/* prototype(s) */
struct remote *init_remote(struct remote **remote, int *responces);

int
main(int argc, char **argv)
{
  /* struct remote *root = init_remote(); */
  
  struct remote *root = NULL;
  int i, responces;
  
  if(argc > 2) printf("%s %s", argv[0], argv[1]);

  root = (struct remote *) init_remote(&root, &responces);

  for(i = 0; i < responces; ++i)
    printf("%s %s\n", root[i].addr, root[i].name);
  
  return EXIT_SUCCESS;
}

struct remote *
init_remote(struct remote **r, int *resps)
{
  int i = 0;
  inquiry_info *info;
  /* struct remote *r = (struct remote *) malloc(sizeof(struct remote)); */
  struct host *h = (struct host *) malloc(sizeof(struct host));

  /* just in case either device_id or socket
   * had issues while initializing.. 
   */
  if((h->device_id = hci_get_route(NULL)) < 0 ||
     (h->socket = hci_open_dev(h->device_id)) < 0) {
    fprintf(stderr, "error while opening the socket");
    exit(1);
  }

  info = (inquiry_info *) malloc(MAX_RESPONSES * sizeof(inquiry_info));
  
  h->length = 8;
  h->flags = IREQ_CACHE_FLUSH;
  
  /* read documentation.. */
  *resps = hci_inquiry(h->device_id,
			      h->length,
			      MAX_RESPONSES, /* number of respones */
			      NULL,	     /* lap?? */
			      &info,
			      h->flags);

  r = (struct remote **) malloc((*resps) * sizeof(struct remote*));
  
  while(i < (*resps)) {
    r[i] = (struct remote *) malloc(sizeof(struct remote));
    memset(r[i]->name, 0, sizeof(r[i]->name));
    ba2str(&(info)->bdaddr, r[i]->addr);
    
    /* in case the device has no name, set name to UNKNOWN */
    if(hci_read_remote_name(h->socket,
			    &(info + i)->bdaddr,
			    sizeof(r[i]->name), r[i]->name, 0) < 0)
      strcpy(r[i]->name, "UNKNOWN");
    ++i;
  }

  free(info);

  return *r;
}
