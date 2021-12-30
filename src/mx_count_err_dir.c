#include "uls.h"

int mx_count_err_dir(char **argv, int argc)
{
    int k = 0;
    int e = 0;
    for (k = 1; k < argc; k++)
    {
        if (argv[k][0] != '-')
        {
            break;
        }
    }

    for (int i = k; i < argc; i++)
    {
        DIR *directory = opendir(argv[i]);
        if (directory == NULL && errno != ENOTDIR && errno != EACCES)
        {
            struct stat info;
            if (lstat(argv[i], &(info)) == -1)
            {
                e++;
            }
        }
    }
    return e;
}
