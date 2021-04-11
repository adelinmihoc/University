#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
  int f = 0, sum = 0;

  f = open("file.txt", O_RDONLY);

  read(f, &sum, sizeof(int));

  printf("Sum is %d\n", sum);

  close(f);

  return 0;
}
