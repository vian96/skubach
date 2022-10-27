#include <unistd.h>
#include <sys/wait.h>

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

#include <string>

int main() {
    int fd[2];
    pipe(fd);
    pid_t fork_id = fork();

    if (fork_id == 0) { // child
        close (fd[0]);
        dup2(fd[1], 1);
        execl("./.my_ls", "./.my_ls", NULL);
        // printf ("Ended reading!\n");
    }
    else { // parent
        // return 0;

        // int status = 0;
        // wait (&status);

        close (fd[1]);
        char buf[64] = {};
        std::string names = {};
        while (1) {
            int len = read (fd[0], buf, 64);
            names.append(buf);
            // fwrite (buf, len, 1, stdout);
            if (len < 64)
                break;
        }

        // printf("%s\n\n\nALL\n", names.c_str());
        int cur_pos = 0;
        while (1) {
            int end_name = names.find('\n', cur_pos);
            // printf("%d\n", end_name);
            if (end_name == std::string::npos)
                break;
            std::string fil_name = names.substr(cur_pos, end_name - cur_pos);
            if (fil_name.size() < 1)
                break;
            cur_pos = end_name + 1 ;
            FILE *f_from = fopen(fil_name.c_str(), "r");
            
            printf("\n%s:\n", fil_name.c_str());
            char buf[64] = {};
            while (fgets (buf, 64, f_from) != NULL)
                printf("%s", buf);
                // buf[0]=0;
                // puts(buf);
                // fputs(buf, stdin);

            fclose(f_from);
        }

        printf ("Ended parent\n");
    }
}