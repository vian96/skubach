#include <unistd.h>
#include <sys/wait.h>

#include <stdlib.h>
#include <stdio.h>

int main() {
    int n = 0;
    printf ("Input len of arr\n");
    scanf ("%d", &n);

    int fd[2];
    pipe(fd);
    pid_t fork_id = fork();

    if (fork_id == 0) { // child
        int x = 0;
        for (int i = 0; i < n; i++) {
            scanf ("%d", &x);
            write (fd[1], &x, sizeof (x));
        }
        printf ("Ended reading!\n");
    }
    else { // parent
        // int status = 0;
        // wait (&status);
        
        printf ("Started parent\n");
        // close (fd[1]); // because parents only reads 
        int x = 0, sum = 0;
        for (int i = 0; i < n; i++) {
            read (fd[0], &x, sizeof (x));
            sum += x;
        }
        printf ("Sum is %d\n", sum);
    }
}