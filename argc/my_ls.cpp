#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

#include <vector>

void print_dir (const char *f_name, bool flag_a, bool flag_l, bool flag_R);

void print_file (dirent *dnt, bool flag_a, bool flag_l, const char *path);

void print_permissions (struct stat struct_buf);

#define DEB(...)

// #define DEB(...) printf(__VA_ARGS__)


// char *path_buffer = (char*) calloc(PATH_MAX, sizeof (char));
// int dir_end = 0;

int main (int argc, char **argv) {
    const struct option long_option[] =
    {
        {"all", no_argument, NULL, 'a'},
        {"long", no_argument, NULL, 'l'}, 
        {"recursive", no_argument, NULL, 'R'},
        {NULL, no_argument, NULL, 0}
    };
	int long_index = 0;
    int opt = 0;
    const char short_option[] = "alR";
    
    bool flag_a = 0, flag_l = 0, flag_R = 0;
    
    while((opt = getopt_long(argc, argv, short_option, long_option, &long_index)) != -1)
    {
        switch(opt)
        {
        case 'a': flag_a = 1;
            break;
        case 'l': flag_l = 1;
            break;
        case 'R': flag_R = 1;
            break;
        case '?': printf("Unknown parameter: -%c\n", optopt);
        }
    }
    
    
    const char *f_name = NULL;
    if (argc >= optind + 1)
        f_name = argv[optind];
    else
        f_name = ".";

    // strcpy (path_buffer, f_name);
    // dir_end = strlen (path_buffer);
    // path_buffer[dir_end] = '/';
    // dir_end++;

    print_dir (f_name, flag_a, flag_l, flag_R);
}

void print_dir (const char *f_name, bool flag_a, bool flag_l, bool flag_R) {
    DEB ("Entering %s dir\n", f_name);
    DIR *dir = opendir (f_name);
    if (!dir) {
        printf ("ERROR: failed to open file, try checking name\n");
        return;
    }

    std::vector<dirent *> directories;

    dirent *dnt = readdir (dir);
    while (dnt) {
        // DEB ("Entered loop\n");
        if (flag_R) {
            // DEB ("Entered R flag\n");
            if (!flag_a && dnt->d_name[0] == '.') {
                dnt = readdir (dir);
                continue;
            }

            if (dnt->d_type == DT_DIR) {
                DEB ("Found dir\n");
                directories.push_back (dnt);
            }
        }
        
        DEB ("Going to print_file %s\n", dnt->d_name);
        print_file (dnt, flag_a, flag_l, f_name);
        DEB ("Ended to print_file\n");
        dnt = readdir (dir);
        DEB ("Ended loop\n");
    }

    DEB ("Finishing while\n");

    if (flag_R)
        while (directories.size()) {
            // printf("\n");

            dirent *entry = directories.back();
            directories.pop_back();

            char file_path[PATH_MAX] = {};
            sprintf (file_path, "%s/%s", f_name, entry->d_name);
            printf ("\n\n%s:\n", file_path);

            print_dir (file_path, flag_a, flag_l, flag_R);
            // printf ("\n");
        }

    
    DEB ("\nended while\n");
    // printf ("\n");
    closedir (dir);

    /* 
    if (flag_R) {
        DEB ("trying opendir %s\n", f_name);
        dir = opendir (f_name);
        DEB ("trying readdir\n");
        dnt = readdir (dir);

        while (dnt) {
            if (!flag_a && dnt->d_name[0] == '.')
                continue;

            strcat (path_buffer, dnt->d_name);
            // printf ("path: %s\n", path_buffer);
            struct stat struct_buf = {};
            stat (path_buffer, &struct_buf);

            if ((S_ISDIR (struct_buf.st_mode))) {
                DEB ("Found dir\n");
                printf ("%s\n", path_buffer);
                print_dir (path_buffer, flag_a, flag_l, flag_R);
            }

            dnt = readdir (dir);
            path_buffer[dir_end] = 0;
        }
        
        printf ("\n");
        closedir (dir);
    }
    // */
}

void print_file (dirent *dnt, bool flag_a, bool flag_l, const char *path) {
    if (!flag_a && dnt->d_name[0] == '.')
        return;
    if (!flag_l) {
        printf ("%s\t", dnt->d_name);
       return;
    }

    char file_path[PATH_MAX] = {};
    sprintf (file_path, "%s/%s", path, dnt->d_name);

    // strcat (path_buffer, dnt->d_name);
    // printf ("path: %s\n", path_buffer);
    struct stat struct_buf = {};
    stat(file_path, &struct_buf);

    print_permissions (struct_buf);
    printf (" %4u", struct_buf.st_nlink);
    printf (" %s\t", getpwuid (struct_buf.st_uid)->pw_name);
    printf (" %s\t", getgrgid (struct_buf.st_gid)->gr_name);
    printf ("%u", struct_buf.st_size);

    const char *time_str = ctime (&struct_buf.st_ctime) + 4; // +4 is to skip weekday name
    printf ("\t%.*s", strlen (time_str) - 1, time_str);
    printf (" %s\n", dnt->d_name);

    // path_buffer[dir_end] = 0;
}

void print_permissions (struct stat struct_buf) {
    printf ((S_ISDIR (struct_buf.st_mode)) ? "d" : "-");
    printf ((struct_buf.st_mode & S_IRUSR) ? "r" : "-");
    printf ((struct_buf.st_mode & S_IWUSR) ? "w" : "-");
    printf ((struct_buf.st_mode & S_IXUSR) ? "x" : "-");
    printf ((struct_buf.st_mode & S_IRGRP) ? "r" : "-");
    printf ((struct_buf.st_mode & S_IWGRP) ? "w" : "-");
    printf ((struct_buf.st_mode & S_IXGRP) ? "x" : "-");
    printf ((struct_buf.st_mode & S_IROTH) ? "r" : "-");
    printf ((struct_buf.st_mode & S_IWOTH) ? "w" : "-");
    printf ((struct_buf.st_mode & S_IXOTH) ? "x" : "-");
}

/* 
-l data
    The file type.
    The file permissions.
    Number of hard links to the file.
    File owner.
    File group.
    File size.
    Date and Time.
    File name.
*/
