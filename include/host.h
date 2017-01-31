# ifndef HOST_H
# define HOST_H
# define MAX_RESPONSES 255	/* pow(2, 8) */
# include "../include/lib.h"
# pragma pack(push)  /* push current alignment to stack */
# pragma pack(1)     /* set alignment to 1 byte boundary */

struct host{
  int device_id, socket, length;
  long flags;
};
# pragma pack(pop) /* restore original alignment from stack */

struct host *init_host();


# endif
