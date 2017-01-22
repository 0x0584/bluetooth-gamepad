/* remember this.. now you are about to create this application 
 * and you are motivated enough to write this, don't be superfecial 
 * and make this shit done at time.. you're about hell! did you know
 * this?? you are at the edge, be careful so that you don't fall..  
 *
 * Cheers!
 */

/* you have oast with this library.. 
 * get it done this time! */
#include <errno.h>		/* ensure you understand this library this time.. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

/* Bluez bluetooth libraries */
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>

#define MAX_RESPONSES 255	/* pow(2, 8) */

int
main(int argc, char **argv)
{
  int device_id;
  int socket;

  /* just in case either device_id or socket
   * had issues while initializing.. 
   */
  if((device_id = hci_get_route(NULL)) < 0 ||
     (socket = hci_open_dev(DeviceId)) < 0)
    exit(1);

  
  return EXIT_SUCCESS;
}
