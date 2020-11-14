#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

int main() {
  const int SIZE = 4096;
  const char *name = "OS";
  int shm_fd;
  int *ptr;
  int val = 0;

  pid_t pid;
  pid = fork();
  int collatz = 0;

  if(pid < 0){
    fprintf(stderr, "Fork Failed" );
    return 1;
  }
  else if(pid == 0) {/* child process */
    /* create shared memory object */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    /* set the size of the memory object */
    ftruncate(shm_fd, 4096);

    /* memory map the shared memory object */
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
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
      printf(ptr.val, "%d", collatz);
      ptr = ptr->next;

      if(collatz % 2 == 0){
        collatz = collatz / 2;
        if (collatz == 1) {
          printf(ptr, "%d", collatz);
          break;
        }
      }
      else{
        collatz = (collatz * 3) + 1;
      }

    } //end while loop
  }
  else{ /* parent process */
    /* parent will wait for child process to complete */
    wait(NULL);

    /* create shared memory object */
    shm_fd = shm_open(name, O_RDONLY, 0666);

    /* memory map the shared memory object */
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    while(ptr != NULL){
      printf("%d", ptr);
      ptr = ptr->next;
    }

    /* remove the shared memory object */
    shm_unlink(name);
  }

  return 0;
}
