#include "uls.h"

void print_err_open_dir(char **error_dir, int count_file_err)
{
    for (int i = 0; i < count_file_err; i++)
    {
        mx_printerr("uls: ");
        perror(error_dir[i]);
        error_dir[i] = NULL;
    }
}

void static print_dir(int i_total, t_ls **files, t_main *main)
{
    int i = 0;
    int k = 0;
    for (; files[i]; i++)
        ;
    for (; main->dir[k]; k++)
        ;
    for (int k = 0; k < i; k++)
    {

        if (files[k]->type == 'd')
        {
            if (i != 1 || k > 0)
            {
                mx_printstr(files[k]->print_name);
                mx_printstr(":\n");
            }
            mx_ls_loop(i_total, mx_read_dir(files[k]->name, 0), main->flags, main);
        }
        if (k < i - 1)
            mx_printchar('\n');
    }
}

void static print_files_without_dir(int str_size, int str_size_file, t_main *main, t_ls **files, t_ls **out_files)
{
    char **files_out = mx_until_create_char_arr(str_size_file);
    char **files_without_dir = mx_until_create_char_arr(str_size);

    int k = 0;
    int k1 = 0;
    int k2 = 0;

    if (!str_size && !str_size_file)
    {
        mx_ls_loop(k1, mx_read_dir(".", 0), main->flags, main);
    }

    // вывод файлов которые ввел даун
    for (int i = 0; i < str_size_file; i++)
    {
        out_files[i] = mx_get_lstat(main->dir[i]);
    }
    out_files[str_size_file] = NULL;

    for (int i = 0; out_files[i]; i++)
    {
        files_out[k1] = mx_strdup(out_files[i]->name);
        k1++;
    }

    // вывод папок которые ввел даун
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
        k2++;
    }

    mx_ls_loop(k1, files_out, main->flags, main);
    if (k1 && k2)
        mx_printchar('\n');
    k1 = 0;
    mx_ls_loop(k1, files_without_dir, main->flags, main);
    print_dir(k1, files, main);
}

void mx_create_ls(t_main *main)
{
    int str_size = mx_until_get_size_arr(main->files);
    int str_size_file = mx_until_get_size_arr(main->dir);

    t_ls **files = mx_ls_create_struct_arr(str_size);
    t_ls **out_files = mx_ls_create_struct_arr(str_size_file);

    print_err_open_dir(main->error_dir, main->count_file_err);
    print_files_without_dir(str_size, str_size_file, main, files, out_files);
}
