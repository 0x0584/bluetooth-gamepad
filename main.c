/* remember this.. now you are about to create this application 
 * and you are motivated enough to write this, don't be superfecial 
 * and make this shit done at time.. you're about hell! did you know
 * this?? you are at the edge, be careful so that you don't fall..  
 *
 * Cheers!
 */

/* you have oast with this library.. 
 * get it done this time! 
 * NOTE: i didn't know what i was thinking of when i wrote `oast`
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
# define NAME_MAX_SIZE 255
# define ADDRESS_MAX_SIZE 20

struct remote{
  int device_id, socket;
  char name[NAME_MAX_SIZE],
    addr[ADDRESS_MAX_SIZE];
};

struct remote *init_remote(void);
int
main(int argc, char **argv)
{

  struct remote *root = init_remote();

  printf("%s %s\n", root->addr, root->name);
  
  return EXIT_SUCCESS;
}

struct remote *
init_remote(void)
{
  int i;
  struct remote *proto = (struct remote *) malloc(sizeof(struct remote));

  /* just in case either device_id or socket
   * had issues while initializing.. 
   */
  if((proto->device_id = hci_get_route(NULL)) < 0 ||
     (proto->socket = hci_open_dev(proto->device_id)) < 0)
    exit(1);

  inquiry_info *info = (inquiry_info *) malloc(MAX_RESPONSES * sizeof(inquiry_info));

  /* read documentaion.. */
  int responses = hci_inquiry(proto->device_id,
			      8,
			      MAX_RESPONSES,
			      NULL,
			      &info,
			      IREQ_CACHE_FLUSH);

  for(i = 0; i < responses; ++i) {
    memset(proto->name, 0, sizeof(proto->name));
    
    /* Umm, really? WHAT'S ba in ba2tr? */
    ba2str(&(info)->bdaddr, proto->addr);
    
    /* in case the device has no name, set name to UNKNOWN */
    if(hci_read_remote_name(proto->socket, &(info + i)->bdaddr,
			    sizeof(proto->name), proto->name, 0))
      strcpy(proto->name, "UNKNOWN");
    /* printf("%s %s\n", proto->addr, proto->name); */
  }

  free(info);

  return proto;
}
