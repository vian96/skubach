#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
    if (argc < 2) {
        printf ("ERROR: Not enough args!\n");
        return 0;
    }
    FILE *f_from = fopen (argv[1], "r");
    FILE *f_to   = fopen (argv[2], "w");

    const int BUF_SIZE = 64;
    char *buf = (char*) calloc (BUF_SIZE, sizeof (char));
    while (fgets (buf, BUF_SIZE, f_from) != NULL)
        fputs (buf, f_to);

    fclose (f_from);
    fclose (f_to);
}
