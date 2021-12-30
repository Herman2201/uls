#include "uls.h"

void static mx_ls_sort_default(char **arr)
{
    char *temp;
    int size = mx_until_get_size_arr((char **)arr);

    for (int i = 0; i < size; ++i)
    {
        for (int j = i; j < size; ++j)
        {
            if (mx_strcmp(arr[i], arr[j]) > 0)
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

char **mx_create_param_dir(char **argv, int argc)
{
    char **files_name = mx_until_create_char_arr(argc);
    int k = 0;
    int f = 0;

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
        if (directory == NULL)
        {
            struct stat info;
            if (!(lstat(argv[i], &(info)) == -1))
            {
                files_name[f] = mx_strdup(argv[i]);
                f++;
            }
        }
    }

    mx_ls_sort_default(files_name);
    return files_name;
}
