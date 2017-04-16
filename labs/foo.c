# include <stdio.h>

int
main()
{
  /* printf("  j\ni\n"); */
  for(int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j)
      printf("  (%d << %d) %d", i, j, i<<j);
  printf("\n");
}
  return 0;
}
