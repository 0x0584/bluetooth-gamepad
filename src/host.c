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
