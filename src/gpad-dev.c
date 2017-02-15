#include "../include/gpad.h"

void
pinfo(gpad_t *dev)
{
  printf("[fd:%d] %s (path: %s)\n[axes: %u | buttons: %u]\n", dev->info->fd,dev->info->name, dev->info->path, dev->info->naxes, dev->info->nbuttons);
}

gpad_t *
ginit()
{
  static unsigned int i = 0;
  char buffer[256], *path = "/dev/input/js";

  gpad_t *gtemp = (gpad_t *) malloc(sizeof(gpad_t));
  gtemp->info = (gpad_info *) malloc(sizeof(gpad_info));
  gtemp->info->fd = -1;

  sprintf(buffer, "%s%u", path, (gtemp->info->id = ++i));
  gtemp->info->path = strdup(buffer);
  
  if((gtemp->info->fd = open(buffer, O_RDONLY | O_NONBLOCK)) == -1)
    return NULL;
  else {
    ginfo(gtemp);
    pinfo(gtemp);
  }
  
  return gtemp;
}


void
ginfo(gpad_t *dev)
{
  int naxes = 0, nbuttons = 0;
  char name[128];
  struct js_event *tjse;
  
  ioctl(dev->info->fd, JSIOCGAXES, &naxes);
  ioctl(dev->info->fd, JSIOCGBUTTONS, &nbuttons);
  ioctl(dev->info->fd, JSIOCGNAME(sizeof(name)), &name);
  tjse =  (struct js_event *) malloc(sizeof(struct js_event));

  dev->info->naxes = naxes;
  dev->info->nbuttons = nbuttons;
  
  dev->axes = (gpad_axe *) malloc((naxes) * sizeof(gpad_axe));
  dev->buttons = (gpad_butn *) malloc((nbuttons) * sizeof(gpad_butn));
  dev->info->name = strdup(name);
  dev->jse = tjse;
}

void 
gkill(gpad_t *dev)
{
  free(dev->axes);
  free(dev->buttons);
  free(dev->info->name);
  free(dev->info);
  free(dev->jse);
  free(dev);
}
