#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ftw.h>
#include <dlfcn.h>
#include <limits.h>
#include <errno.h>
#include "plugin_api.h"
#include <inttypes.h>
#include <limits.h>





int show_version(char *ve)
{
    printf("Version %s\n", ve);
    return 0;
}

int show_help(int x)
{
    printf("------------------DESCRIPTION----------------=\n");
    printf("=This program searches for plugins in *.so   =\n");
    printf("=and uses them to find files with            =\n");
    printf("=different criteria.                         =\n");
    printf("=--------------------USAGE-------------------=\n");
    printf("=      ./lab1 [[options] directory]          =\n");
    printf("=  If there is no any directory in command,  =\n");
    printf("=             shows this page                =\n");
    printf("=-------------------OPTIONS------------------=\n");
    printf("=-h\t shows this page                        =\n");
    printf("=-v\t show version of program                =\n");
    printf("=-P\t add path to plugins directory          =\n");
    printf("=-l\t add path to log file                   =\n");
    printf("=-C\t add condition for searching            =\n");
    printf("=-N\t inversion of searching criteria        =\n");
    printf("---------------------------------------------=\n");
    exit(0);
}
