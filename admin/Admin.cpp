//
// Created by rusla on 10/13/2019.
//

#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sys/param.h>
#include <string>
#include <pwd.h>
#include <sys/stat.h>
#include <unistd.h>
#include <grp.h>

using namespace std;


/* adduser.c
Add Users, Set Up Profiles,
Set The Password And Email

*/

int adduser(int argc, char **argv)
{

    struct passwd *userlist;
    int count, usernumber;
    FILE *tmp, *stmp, *profile;
    char *commentfield, *username, *userdir, *home;
    char reply;

    commentfield = (char *)malloc(1024*sizeof(char));
    username = (char *)malloc(8*sizeof(char));
    userdir = (char *)malloc(256*sizeof(char));
    home = (char *)malloc(256*sizeof(char));

    if (argc != 4) {
        printf("Usage: %s [dirname - no slashes ] [ logname ] [ comment - in quotes ]\n", argv[0]);
        exit(1);
    }

    if (strlen(argv[2]) > 8 || strlen(argv[2]) < 5) {
        printf("Please choose a logname between 5 and 8 characters!\n");
        exit(1);
    }

    signal(SIGHUP, SIG_IGN);
    signal(SIGINT, SIG_IGN);

    setpwent();

    count = 0;

    while ((userlist = getpwent()) != NULL) {
        if (count < userlist->pw_uid) {
            count = userlist->pw_uid;
            usernumber = count+1;
        }
    }

    endpwent();

    sprintf(commentfield, "%s", argv[3]);
    sprintf(userdir, "%s", argv[1]);
    sprintf(username, "%s", argv[2]);
    sprintf(home, "/%s/%s", argv[1], argv[2]);

    printf("\n");
    printf("Check this out before proceeding!!!\n");
    printf("-----------------------------------\n");
    printf("Logname:\t%s\n", username);
    printf("Homedir:\t/%s/%s\n", userdir, username);
    printf("Comment:\t%s\n", commentfield);
    printf("-----------------------------------\n");
    printf("\n");

    printf("\n");
    printf("All of this ok?\n");
    printf("\n");
    printf("y or n [n is the default]\n");
    printf("\n");

    scanf("%c", &reply);

    if ( reply != 'y') {
        printf("\n");
        printf("All right, give it another shot if you want!\n");
        exit(0);
    }

    tmp = fopen("/etc/passwd", "a");
    fprintf(tmp, "%s:x:%d:1:%s:/%s/%s:/bin/bash\n", username, usernumber, commentfield, userdir, username);
    fclose(tmp);

    stmp = fopen("/etc/shadow", "a");
    fprintf(stmp, "%s:*LK*:::::::\n", username);
    fclose(stmp);

    mkdir(home, 0755);
    chdir(home);

    profile = fopen(".profile", "a");
    fprintf(profile, "stty istrip\n");
    fprintf(profile, "PATH=/bin:/usr/bin:/usr/local/bin:/usr/share/bin:.\n");
    fprintf(profile, "export PATH\n");
    fprintf(profile, "\n");
    fprintf(profile, "\n");
    fclose(profile);

    chown(home, usernumber, 1);
    chown(".profile", usernumber, 1);
    chmod(".profile", 0644);



    printf("Set the Password!\n");
    printf("\n");
    execl("/usr/bin/passwd", "passwd", username, NULL);
    printf("\n");
    printf("Password set\n");

}

int myChmod(int argc, char **argv)
{
    string str;

    if (argc != 3) {
        printf("Usage: %s [permission oct representation] [ file dir ] \n", argv[0]);
        return 1;
    }

    if (strlen(argv[1]) != 3) {
        printf("Please set a 3 number permission representation\n");
        return 1;
    }
    str = argv[1];
    for(char& c : str) {
        if ('7' - c < 0 || '7' - c > 7){
            printf("Please set a value between 0 to 7\n");
            return 1;
        }
    }

    str.insert(0, "0");
    chmod(argv[2], stoi(str));
    printf("Chmod successful\n");


}


void do_chown(const char *file_path,
               const char *user_name,
               const char *group_name)
{
    uid_t          uid;
    gid_t          gid;
    struct passwd *pwd;
    struct group  *grp;

    pwd = getpwnam(user_name);
    if (pwd == NULL) {
        printf("Failed to get uid");
        return;
    }
    uid = pwd->pw_uid;

    grp = getgrnam(group_name);
    if (grp == NULL) {
        printf("Failed to get gid");
        return;

    }
    gid = grp->gr_gid;

    if (chown(file_path, uid, gid) == -1) {
        printf("chown fail");
        return;

    }
}


void myChown(int argc, char **argv)
{
    do_chown(argv[0], argv[1], argv[2]);
}