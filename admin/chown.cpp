//
// Created by rusla on 10/1/2019.
// https://stackoverflow.com/questions/8778834/change-owner-and-group-in-c
#include <sys/types.h>
#include <pwd.h>

void myChown(int argc, char **argv)
{
    do_chown(argv[0], argv[1], argv[2]);
}


void do_chown (const char *file_path,
               const char *user_name,
               const char *group_name)
{
    uid_t          uid;
    gid_t          gid;
    struct passwd *pwd;
    struct group  *grp;

    pwd = getpwnam(user_name);
    if (pwd == NULL) {
        die("Failed to get uid");
    }
    uid = pwd->pw_uid;

    grp = getgrnam(group_name);
    if (grp == NULL) {
        die("Failed to get gid");
    }
    gid = grp->gr_gid;

    if (chown(file_path, uid, gid) == -1) {
        die("chown fail");
    }
}
