#include <getopt.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>
#include <unistd.h>
#include <utime.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <errno.h>

int main (int argc, char **argv) {
    const struct option long_option[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"verbose", no_argument, NULL, 'v'}, 
        {"interactive", no_argument, NULL, 'i'},
        {"force", no_argument, NULL, 'f'},
        {"preserve", no_argument, NULL, 'p'},
        {NULL, no_argument, NULL, 0}
    };
	int long_index = 0;
    int opt = 0;
    const char short_option[] = "hvifp";
    
    bool flag_h = 0, flag_v = 0, flag_i = 0, flag_f = 0, flag_p = 0;
    
    while((opt = getopt_long(argc, argv, short_option, long_option, &long_index)) != -1)
    {
        switch(opt)
        {
        case 'h': flag_h = 1;
            break;
        case 'v': flag_v = 1;
            break;
        case 'i': flag_i = 1;
            break;
        case 'f': flag_f = 1;
            break;
        case 'p': flag_p = 1;
            break;
        case '?': 
            printf ("Unknown parameter: -%c\n", optopt);
        }
    }
    
    if (flag_h) {
        printf ("This is hello for the program!\n"
                "I am too lazy to write it\n"
                "So let us both pretend help is there\n");
        return 0;
    }

    if (argc < optind + 2) {
        printf ("ERROR: not enough file names!\n");
        return 0;
    }

    const char *from_name = argv[optind], *to_name = argv[optind + 1];

    if (flag_i && access(to_name, F_OK) == 0) { // file exists
        printf ("Are you sure you want to rewrite %s?\n", to_name);
        const int ANSWER_SIZE = 128;
        char answer[ANSWER_SIZE] = {};

        fgets (answer, ANSWER_SIZE, stdin);
        if (toupper (answer[0]) != 'Y') {
            printf ("Fine, i will not copy\n");
            return 0;
        }
        printf ("Ok, I will copy\n");
    }

    FILE *f_to = fopen (to_name, "w");
    if (f_to == NULL) { // failed to open
        if (errno == EACCES) {
            if (flag_f) {
                remove (to_name);
                f_to = fopen (to_name, "w");
            }
            else {
                printf ("ERROR: no access to written file\n");
                return 0;
            }
        }

        if (errno != EACCES) { // another if because error may occur at second open
            printf ("ERROR opening written file, errno is %d\n", errno);
            return 0;
        }
    }

    FILE *f_from = fopen (from_name, "r");
    if (f_from == NULL) {
        printf ("ERROR opening read file, errno is %d\n", errno);
        return 0;
    }

    const int BUF_SIZE = 64;
    char buf[BUF_SIZE] = {};
    while (fgets (buf, BUF_SIZE, f_from) != NULL)
        fputs (buf, f_to);

    if (flag_p) {
        struct stat struct_buf = {};
        stat(from_name, &struct_buf);

        chmod (to_name, struct_buf.st_mode);
        chown (to_name, struct_buf.st_uid, struct_buf.st_gid);

        utimbuf timbuf = {
            .actime = struct_buf.st_atim.tv_sec, 
            .modtime = struct_buf.st_mtim.tv_sec
        };
        utime (to_name, &timbuf);
    }

    fclose (f_from);
    fclose (f_to);

    if (flag_v)
        printf ("%s > %s\n", from_name, to_name);
}
