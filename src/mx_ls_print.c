#include "uls.h"

static int mx_get_terminal_width()
{
    struct winsize term;

    ioctl(0, TIOCGWINSZ, &term);
    return term.ws_col;
}

int static get_max_len(char **files)
{
    int max_len = 0;

    if (files)
    {
        for (int i = 0; files[i]; i++)
        {
            if (mx_strlen(files[i]) > max_len)
            {
                max_len = mx_strlen(files[i]);
            }
        }
    }
    return max_len;
}

void mx_ls_print(t_ls **files, int file_n, char *flags)
{
    char **files_name = mx_until_create_char_arr(file_n + 1); //массив для хранения имен файлов

    for (int i = 0; i < file_n; i++)
    {
        files_name[i] = mx_strdup(files[i]->print_name);
    }
    if (mx_is_l_flag(flags, 'l'))
    {
        mx_ls_print_l(files, file_n, flags);
    }
    else
    {
        mx_ls_print_big_c(files_name, file_n, get_max_len(files_name), mx_get_terminal_width());
    }
}
