#include "../include/gpad.h"
/* #include <dirent.h> */

gpad_t *
ginit()
{
  /* local prototypes */
  void pinfo(gpad_t *);
  
  static unsigned int i = 0;	/* the id of each new device */
  char buffer[256], *path = "/dev/input/js";

  /* allocate memory */
  gpad_t *gtemp = (gpad_t *) malloc(sizeof(gpad_t));
  //  memset(gtemp, 0x00, sizeof(gpad_t));
  
  gtemp->info = (gpad_info *) malloc(sizeof(gpad_info));

  /* initializion */
  gtemp->info->fd = -1;
  gtemp->info->isconnected = false;

  sprintf(buffer, "%s%u", path, (gtemp->info->id = ++i));
  gtemp->info->path = strdup(buffer);
  
  if((gtemp->info->fd = open(buffer, O_RDONLY | O_NONBLOCK)) == -1)
    goto FAIL;
  else ginfo(gtemp);
  
#ifdef DEBUG
  pinfo(gtemp);
#endif

  return gtemp;

 FAIL:

  free(gtemp);
  return NULL;
}

gpad_t *
ginfo(gpad_t *dev)
{  
  int naxes = 0, nbuttons = 0;
  char name[128];
  struct js_event *jse;
  
  ioctl(dev->info->fd, JSIOCGAXES, &naxes);
  ioctl(dev->info->fd, JSIOCGBUTTONS, &nbuttons);
  ioctl(dev->info->fd, JSIOCGNAME(sizeof(name)), &name);
  jse =  (struct js_event *) malloc(sizeof(struct js_event));

  dev->info->naxes = naxes;
  dev->info->nbuttons = nbuttons;
  dev->info->name = strdup(name);
  
  unsigned int statesz = (sizeof(gpad_axe) + sizeof(gpad_butn));

  dev->state = malloc(sizeof(statesz));
  dev->state->axe = (gpad_axe *) malloc(sizeof(gpad_axe));
  dev->state->button = (gpad_butn *) malloc(sizeof(gpad_butn));
  dev->e = jse;

  dev->info->isconnected = true;

  return dev;
}

void 
gkill(gpad_t *dev)
{
  if(!isnull(dev)) {
    close(dev->info->fd);
    
    free(dev->info->name);
    free(dev->info);
    free(dev->state->axe);
    free(dev->state->button);
    free(dev->state);
    free(dev->e);
    free(dev);
  }
}

void
pinfo(gpad_t *dev)
{
  printf("(state: %s fd:%d id:%d) %s\n(path: %s)\n[axes: %u | buttons: %u]\n",
	 dev->info->isconnected ? "CONNECTED":"DISCONNECTED",
	 dev->info->fd,
	 dev->info->id,
	 dev->info->name,
	 dev->info->path,
	 dev->info->naxes,
	 dev->info->nbuttons);
}
