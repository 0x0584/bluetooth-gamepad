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

# include "../include/remote.h"
# include "../include/host.h"

struct remote *
init_remote(struct remote **r, int *resps)
{
  int i = 0;
  inquiry_info *info; 

  /* struct remote *r = (struct remote *) malloc(sizeof(struct remote)); */
  struct host *h = init_host(resps);
  
  info = (inquiry_info *) malloc(MAX_RESPONSES * sizeof(inquiry_info));

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
  free(h);
  return *r;
}
