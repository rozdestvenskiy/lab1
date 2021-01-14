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

struct plugin{
    void *plugin_file;
    struct plugin_info *plugin_info;
    int (*plugin_get_main_function)(const char *fname,
                                    struct option *in_opts[],
                                    size_t in_opts_len,
                                    char *out_buff,
                                    size_t out_buff_len);
    int option_number;
    int found_option;
};


