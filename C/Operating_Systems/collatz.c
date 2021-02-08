#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  pid_t pid;
  pid = fork();
  int collatz = 0;

  if(pid < 0){
    fprintf(stderr, "Fork Failed" );
    return 1;
  }
  else if(pid == 0) {/* child process */
    // printf("%d", collatz);
    // printf(", ");
    scanf("%d", &collatz);

    if(collatz < 0){
      fprintf(stderr, "Negative Value");
      return 1;
    }
    else if(collatz == 0){
      fprintf(stderr, "Need Positive Value");
      return 1;
    }

    while(collatz != 1) {
      printf("%d", collatz);
      printf(", ");

      if(collatz % 2 == 0){
        collatz = collatz / 2;
        if (collatz == 1) {
          printf("%d", collatz);
          break;
        }
      }
      else{
        collatz = (collatz * 3) + 1;
      }

    } //end while loop

    printf("\n");
  }
  else{ /* parent process */
    /* parent will wait for child process to complete */
    wait(NULL);
  }

  return 0;
}
