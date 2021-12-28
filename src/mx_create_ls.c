#include "uls.h"

void static print_dir(t_ls **files, t_main *main)
{
    int i = 0;
    for (; files[i]; i++)
        ;
    for (int k = 0; k < i; k++)
    {
        DIR *directory = opendir(files[k]->print_name);
        if (directory == NULL && errno != ENOTDIR && errno != EACCES)
        {
            struct stat info;
            if (lstat(files[k]->print_name, &(info)) == -1)
            {
                mx_printerr("uls: ");
                perror(files[k]->print_name);
                files[k]->print_name = NULL;
                continue;
            }
            else
            {
                mx_ls_loop(&files[k]->name, main->flags, main);
            }
        }
        if (files[k]->type == 'd')
        {
            if (i != 1)
            {
                mx_printstr(files[k]->print_name);
                mx_printstr(":\n");
            }
            mx_ls_loop(mx_read_dir(files[k]->name, 0), main->flags, main);
            // mx_printchar('\n');
        }
    }
}

void static print_files_without_dir(int str_size, t_main *main, t_ls **files)
{
    char **files_without_dir = mx_until_create_char_arr(str_size);
    int k = 0;

    if (!str_size)
    {
        mx_ls_loop(mx_read_dir(".", 0), main->flags, main);
    }

    for (int i = 0; i < str_size; i++)
    {
        files[i] = mx_get_lstat(main->files[i]);
    }
    files[str_size] = NULL;
    for (int i = 0; files[i]; i++)
    {
        files_without_dir[k] = mx_strdup(files[i]->name);
        if (files[i]->type != 'd')
        {
            k++;
        }
        else
        {
            mx_strdel(&files_without_dir[k]);
        }
    }
    mx_ls_loop(files_without_dir, main->flags, main);
    print_dir(files, main);
}

void mx_create_ls(t_main *main)
{
    int str_size = mx_until_get_size_arr(main->files);
    t_ls **files = mx_ls_create_struct_arr(str_size);

    print_files_without_dir(str_size, main, files);
}
