//Citiți o comandă de la tastatură și rulați-o cu fork + exec.


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char**argv) {
  
  if (fork() == 0) {
    execvp(argv[1], argv+1);
    exit(0);
  }
  wait(0);

  return 0;
}
