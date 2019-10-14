# Welcome to my Unix shell!

Hi! This is a simple implementation of a UNIX shell that was done for my school project.


## Supported commands

Here is a list of supported commands ordered by groups.

**Group 1** - simple commands

|Command        |Discription|Example|
|----------------|-------------------------------|-----------------------------|
|ls|`lists files in a directory`           |*User$ ls*            |
|cd         |`moves to a diffrent working directory`           |*User$ cd {Dir Path}*             |
|mkdir|`creates a new directory`|*User$ mkdir{Dir_Path/Dir_Name}*|
|wc|`counts number of lines, words and charchters in a file `|*User$ wc {Path to File}*|
|cat|`shows the file txt`|*User$ cat {Path to File}*|
|tail|`shows the last n lines of a file txt (in case option n is not specified it will print the last 10 lines)`|*User$ tail [options] {Path to File}, e.g User$ tail -n15 myTxt*|
|mv|`moves a file to a diffrent directory`|*User$ mv {file} {Path to move File}*|

**Group 2** - admin commands

|Command        |Discription|Example|
|----------------|-------------------------------|-----------------------------|
|chown|`changes file owner`           |*User$ chown {file path} {user name} {group name}*            |
|chmod         |`changes file permissons`           |*User$ chmod [permission oct representation] [ file dir]*             |
|adduser|`creates a new user`|*User$ adduser [dirname - no slashes ] [ logname ] [ comment - in quotes ]*|

**Group 3** - sys commands

|Command        |Discription|Example|
|----------------|-------------------------------|-----------------------------|
|kill|`kills a runing process`           |*User$ kill [pid]*            |
|ping|`tests the reachability of a host on an Internet Protocol network `           |*User$ ping [host]*             |
|ifconfig|`display interface name and family`|*User$ ifconfig*|

All the commands above are implimented on a light version unlike in an actual unix shell

Commands were written/found using the following guides:

 - https://www.geeksforgeeks.org/making-linux-shell-c/
 - https://gist.github.com/Ogden91/3f03fc913eab66f4d185
 - https://stackoverflow.com/questions/8778834/change-owner-and-group-in-c
 - https://www.geeksforgeeks.org/ping-in-c/
 - https://gist.github.com/Ogden91/c20403ab09eb638fb288
 - http://man7.org/linux/man-pages/man3/getifaddrs.3.html
 - http://www.embhack.com/implementation-of-cat-command/
 - http://wetechies.blogspot.com/2013/05/c-implementation-of-wcword-count-linux.html
 - http://linuxshellaccount.blogspot.com/2008/02/c-code-to-add-user-accounts-and.html

### prerequisite

This UNIX shell is using GNU readline library, make sure you have it installed.
To install the readline library, open the terminal window and write
`sudo apt-get install libreadline-dev`