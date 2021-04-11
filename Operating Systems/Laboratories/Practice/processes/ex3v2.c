#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main() {
  
  //execl("/bin/ls", "/bin/ls", "-l", NULL);
  //execlp("ls", "ls", "-l", NULL);
  system("ls -l");
  return 0;
}
