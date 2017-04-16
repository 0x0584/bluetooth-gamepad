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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * Should you need to contact me, the author, you can do so either by
 * e-mail - mail your message to <rchid.anas@gmail.com>.
 *
 ************************************************************************
 * NOTE:	i guess i'm doing well, as planned. nice!		* 
 *									*
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
#include "../include/gpad.h"

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

  gpad_t *g = ginit();
  /* printf("\n[isnull:%s]\n",isnull(g)); */

  gevent(g);

  gkill(g);

  return EXIT_SUCCESS;
}

/* joke about programming: */
