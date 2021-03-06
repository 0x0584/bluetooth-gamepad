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

#ifndef REMOTE_H
#define REMOTE_H
#define NAME_SIZE 248
#define ADDRESS_SIZE 19
#define MAX_RESPONSES 255	/* pow(2, 8) */
#include <bluetooth/bluetooth.h> /* ba2str(),  */
#include <bluetooth/hci.h>	  /* inquiry_info */
#include "../include/liblue.h"

/* struct(s) */
struct remote{
  char name[NAME_SIZE],
    addr[ADDRESS_SIZE];
};

/* prototype(s) */
struct remote *init_remote(struct remote **remote, int *responces);

#endif
