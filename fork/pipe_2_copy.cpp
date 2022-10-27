#include <unistd.h>
#include <sys/wait.h>

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

int size_of_file (FILE *file) {
    assert (file);
    assert (!ferror (file));

    fseek (file, 0, SEEK_END);
    int size = ftell (file);
    
    fseek (file, 0, SEEK_SET);

    return size;
}

int main() {
    int n = 0;
    printf ("Input name1 -> name2\n");
    char to_name[PATH_MAX] = {};
    char from_name[PATH_MAX] = {};
    scanf ("%s %s", from_name, to_name);

    int fd[2];
    pipe(fd);
    pid_t fork_id = fork();

    if (fork_id == 0) { // child
        close (fd[0]);

        FILE *f_from = fopen (from_name, "rb");
        if (f_from == NULL) {
            printf ("ERROR opening read file\n");
            return 0;
        }

        int sum_write = 0;
        const int BUF_SIZE = 64;
        char buf[BUF_SIZE] = {};
        while (fgets (buf, BUF_SIZE, f_from) != NULL) {
            int writed = 0;
            while (writed != BUF_SIZE) {
                writed += write (fd[1], buf, BUF_SIZE);
            }
            sum_write += writed;
        }

        fclose (f_from);
        close(fd[1]);
        printf ("Read %d bytes \n", sum_write);
        printf ("Ended reading!\n");
    }
    else { // parent
        close (fd[1]);
        printf ("Started parent\n");
        
        FILE *f_to = fopen (to_name, "wb");
        if (f_to == NULL) {
            printf ("ERROR opening write file\n");
            return 0;
        }

        int file_size = 0;
        int sum_write = 0;
        const int BUF_SIZE = 64;
        char buf[BUF_SIZE + 1] = {};
        int whole = 0;
        printf("startedn reading from pipe\n");
        int loop = 0;
        while (1){
            int cnt = read(fd[0], buf, BUF_SIZE);
            whole += cnt;
            fputs (buf, f_to);
            loop++;
            if (cnt < BUF_SIZE - 1)
                break;
        }

        fclose (f_to);
        
        printf ("Wrote %d bytes with %d loops \n", whole, loop);
        printf ("Ended parent\n");
    }
}