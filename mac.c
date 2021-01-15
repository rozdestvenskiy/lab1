#ifndef _PLUGIN_API_H
#define _PLUGIN_API_H

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <regex.h>

#define PATTERN "^[0-9A-F]{2}:[0-9A-F]{2}:[0-9A-F]{2}:[0-9A-F]{2}:[0-9A-F]{2}:[0-9A-F]{2}$"

struct plugin_option {
    struct option opt;
    const char *opt_descr;
};

struct plugin_info {
    const char *plugin_name;
    size_t sup_opts_len;
    struct plugin_option *sup_opts;
};

int plugin_get_info(struct plugin_info* ppi)
{
    if (ppi == NULL)
    {
        return 1;
    }
    ppi->plugin_name = "mac";
    ppi->sup_opts_len = 1;
    struct plugin_option *mac_option = malloc(sizeof(struct plugin_option) * ppi->sup_opts_len);
    mac_option->opt_descr = "Searches mac address";
    struct option *mac_opt = malloc(sizeof(struct option));
    mac_opt->name = "macv4-addr";
    mac_opt->has_arg = required_argument;
    mac_opt->flag = NULL;
    mac_opt->val = 0;
    mac_option->opt = *mac_opt;

    ppi->sup_opts = malloc(sizeof(struct plugin_option));
    ppi->sup_opts->opt.name = "mac-addr";
    ppi->sup_opts->opt.has_arg = required_argument;
    ppi->sup_opts->opt.flag = NULL;
    ppi->sup_opts->opt.val = 0;

    return 0;
};

int plugin_process_file(const char *fname,
                        struct option *in_opts[],
                        size_t in_opts_len,
                        char *out_buff,
                        size_t out_buff_len)
{
    FILE *current_file;
    if ((strstr(fname, "share") != NULL) || (strstr(fname, "/.") != NULL))
    {
    	return 10;
    }
    
    current_file = fopen(fname, "r");
    if (current_file == NULL)
    {
        fclose(current_file);
        
        return -1;
    }
    if (in_opts[0]->flag == NULL)
    {
        printf("Error: missing argument\n");
        fclose(current_file);
        return -1;
    }

    char *mac1 = (char *) in_opts[0]->flag;
    regex_t preg;
    int err,regerr;
    err = regcomp (&preg, PATTERN, REG_EXTENDED);
    if (err != 0)
    {
        char buff[512];
        regerror(err, &preg, buff, sizeof(buff));
        printf("%s\n", buff);
    }

    regmatch_t pm;
    regerr = regexec (&preg, mac1, 0, &pm, 0);
   
    if (regerr != 0)
    {
        char errbuf[512];
        regerror(regerr, &preg, errbuf, sizeof(errbuf));
        //printf("%s\n", errbuf);
        printf("Error: invalid syntax of mac address\n");
        strcpy(out_buff, "invalid syntax");
        exit(1);
        return -1;
    }

    char *s;
    s = malloc(sizeof(char) * 255);
    if (s == NULL)
        {
        	return 10;
        }
        
        if (strlen(s) > 255)
        {
        	return 10;
        }
    int i = 0;
    while (feof(current_file) == 0)
    {
        i++;
        if (i > 400)
        {
            fclose(current_file);
            
            return -1;
        }
        int yy;
        yy = fscanf(current_file, "%s", s);
        if (yy == 0)
        {
        	return 10;
        }
        if (strlen(s) > 255)
        {
        	return 10;
        }
        
        if (s == NULL)
        {
        	return 0;
        }
        if (strstr(s, mac1) != NULL)
        {
            fclose(current_file);
            return 0;
        }
    }
    fclose(current_file);
    return 19;
};

#endif
