# ifndef REMOTE_H
# define REMOTE_H
# define NAME_SIZE 248
# define ADDRESS_SIZE 19
# define MAX_RESPONSES 255	/* pow(2, 8) */
# include <bluetooth/bluetooth.h> /* ba2str(),  */
# include <bluetooth/hci.h>	  /* inquiry_info */
# include "../include/lib.h"

/* struct(s) */
struct remote{
  char name[NAME_SIZE],
    addr[ADDRESS_SIZE];
};

/* prototype(s) */
struct remote *init_remote(struct remote **remote, int *responces);

# endif
