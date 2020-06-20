/*****************************************************************
 * installation layout:
 *
 * $APP_ROOT/bin/
 * $APP_ROOT/bin/app
 * $APP_ROOT/config/
 * $APP_ROOT/config/app.xml
 * $APP_ROOT/lib/
 * $APP_ROOT/lib/libfoo.so
 *
 ****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <libgen.h>

extern void f1();
extern void f2();

/* wrapper of dirname() */
static char* get_dir(const char* path, char* buf)
{
    char self[PATH_MAX];
    char* dir;
    char parent[PATH_MAX];

    strncpy(self, path, strlen(path)+1);
    dir = dirname(self);
    strncpy(buf, dir, strlen(dir)+1);
    return buf;
}

/* get app's root path from  $APP_ROOT/bin/app */
static char* get_app_root(char* buf)
{
    char exe_path[PATH_MAX]; /* exe file's path */
    ssize_t n = readlink("/proc/self/exe", exe_path, PATH_MAX);
    exe_path[n+1] = '\0';

    /* get app root */
    get_dir(exe_path, buf); /* bin */
    get_dir(buf, buf);
    return buf;
}

/* get the config path */
static char* get_conf_path(char* buf)
{
    const char* conf = "config";
    get_app_root(buf);
    strncat(buf, "/", strlen("/")+1);
    strncat(buf, conf, strlen(conf)+1);
    return buf;
}

/* get the config file's full path */
static char* get_conf_file_path(char* fname, char* buf)
{
    get_conf_path(buf);
    strncat(buf, "/", strlen("/")+1);
    strncat(buf, fname, strlen(fname)+1);
    return buf;
}

int main(int argc, char** argv)
{

    char conf_path[PATH_MAX];
    get_conf_file_path("app.xml", conf_path);
    printf("CONFIG_PATH: %s\n", conf_path);

    /* call functions defined in APP_ROOT/lib/libfoo.so */
    f1();
    f2();

    return 0;
}
