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

#ifndef LIB_H
#define LIB_H
#include <errno.h>  /* ensure you understand this library this time.. */
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h> /* ba2str(),  */
#include <bluetooth/hci.h>	  /* inquiry_info */
#include <bluetooth/hci_lib.h>	  /* hci_inquiry(), hci_get_route(), hci_open_device(), IREQ_CAHE_FLUSH */
#include <bluetooth/rfcomm.h>

#endif
