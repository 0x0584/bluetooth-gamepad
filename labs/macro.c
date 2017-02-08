
# define TRUE 1
# define FALSE 0

# include <stdio.h>
# include <stdlib.h>

# define FLAG FALSE

int
main(int argc, char **argv)
{
# if !FLAG
  printf("test 1:%d\n", atoi(argv[1]));
# else
  printf("test 2:%s\n", argv[1]);
# endif

}
