#include <unistd.h>
#include <pwd.h>
#include <grp.h>

#include <stdio.h>
#include <string.h>
#include <assert.h>

void call_id (const char *usr);

bool check_group (const group *grp, const char *usr);

/* struct passwd *getpwnam(const char *name);
    getgrent
    struct group *getgrent(void);
    struct group {
               char   *gr_name;        /* group name *
               char   *gr_passwd;      /* group password *
               gid_t   gr_gid;         /* group ID *
               char  **gr_mem;         /* NULL-terminated array of pointers
                                          to names of group members *
           };
*/

int main() {
    printf ("Hello it is uid:\n");
    call_id ("user");
    printf ("\n");
}

void call_id (const char *usr) {
    assert (usr);

    passwd *pwd = getpwnam ("user");
    printf (
        "uid=%d(%s) gid=%d(%s) groups=%d(%s)", 
        pwd->pw_uid, pwd->pw_name, 
        pwd->pw_gid, pwd->pw_name, 
        pwd->pw_gid, pwd->pw_name
    );

    const group *grp = getgrent();
    while (grp) {
        if (check_group (grp, usr))
            printf (",%d(%s)", grp->gr_gid, grp->gr_name);
        grp = getgrent();
    }

}

bool check_group (const group *grp, const char *usr) {
    assert (grp);
    assert (usr);

    const char *str = NULL;
    for (int i = 0; str = grp->gr_mem[i]; i++)
        if (!strcmp (usr, str))
            return true;
    
    return false;
}


