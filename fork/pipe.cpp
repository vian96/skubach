#include <unistd.h>
#include <sys/wait.h>

#include <stdlib.h>
#include <stdio.h>

int main() {
    int fd[2];
    pipe(fd);
    
    // write (fd[1], "pivo1", 6);

    pid_t fork_id = fork();

    if (fork_id == 0) { // child
        char string[] = "pivo";
        // sleep(3);
        //int size = write (fd[1], string, 6);
        printf ("empty\n");
    }
    else { // parent
        printf ("begin\n");
        close (fd[1]); // because parents only reads 
        char string[10] = {0};
        int size = read (fd[0], string, 6);
        printf ("par %s\n", string);
    }
}