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
