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

# include "../include/host.h"

struct host *
init_host()
{
  struct host *host = (struct host *) malloc(sizeof(struct host));

  /* just in case either device_id or socket
   * had issues while initializing.. 
   */
  if((host->device_id = hci_get_route(NULL)) < 0 ||
     (host->socket = hci_open_dev(host->device_id)) < 0) {
    fprintf(stderr, "error while opening the socket");
    exit(1);
  }
  
  host->length = 8;
  host->flags = IREQ_CACHE_FLUSH; /* 0x0001 */
  
  return host;
}
