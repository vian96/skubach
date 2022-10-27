#include <unistd.h>
#include <sys/wait.h>

#include <stdlib.h>
#include <stdio.h>

int main() {
    printf ("start\n");

    pid_t fork_id = fork();
    // printf ("Forked with id %d and returned is %d\n", getpid(), fork_id);
    if (fork_id == 0) { // this is child
        sleep (2);
        printf (
            "I am child proccess, my id is %d and my parent is %d\n", 
            getpid(), getppid()
        );
    }
    else {
        printf (
            "I am parent, my id is %d, child's id is %d and my parent is %d\n"
            "Now I am waiting my child...\n",
            getpid(), fork_id, getppid()
        );
        int status = 0;
        wait (&status);
    }
}

