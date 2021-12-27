#include "uls.h"

char static *mx_ls_get_rwx_str(unsigned short int file_mode) {
    char *result = mx_strdup("---------");

    for (int i = 0; i < 9; i++)
        switch (i) {
            case 0: if (S_IRUSR == (S_IRUSR & file_mode)) result[0] = 'r'; break;
            case 1: if (S_IWUSR == (S_IWUSR & file_mode)) result[1] = 'w'; break;
            case 2: if (S_IXUSR == (S_IXUSR & file_mode)) result[2] = 'x'; break;
            case 3: if (S_IRGRP == (S_IRGRP & file_mode)) result[3] = 'r'; break;
            case 4: if (S_IWGRP == (S_IWGRP & file_mode)) result[4] = 'w'; break;
            case 5: if (S_IXGRP == (S_IXGRP & file_mode)) result[5] = 'x'; break;
            case 6: if (S_IROTH == (S_IROTH & file_mode)) result[6] = 'r'; break;
            case 7: if (S_IWOTH == (S_IWOTH & file_mode)) result[7] = 'w'; break;
            case 8: if (S_IXOTH == (S_IXOTH & file_mode)) result[8] = 'x'; break;
        }
    return result;
}


void mx_ls_print_l(t_ls **files, int file_n, char *opt)
{
    int max_nlink_len = mx_untill_get_max_nlink(files);
    int max_size_len = mx_untill_get_max_size(files);
    char *time_str = NULL;
    char *temp = NULL;
    long long int total = 0;

    mx_printstr("total ");
    for (int i = 0; i < file_n; i++)
    {
        total += files[i]->blocks;
    }
    mx_printstr(mx_itoa(total));
    mx_printchar('\n');

    for (int i = 0; i < file_n; i++)
    {
        temp = ctime(&files[i]->mtime);
        time_str = mx_strndup(&temp[4], 12);
        mx_printchar(files[i]->type);
        mx_printstr(mx_ls_get_rwx_str(files[i]->mode));
        mx_printstr(" ");
        mx_printstr(" ");
        mx_until_print_format_str(mx_itoa((int)files[i]->nlink), 'r', ' ', max_nlink_len);
        mx_printstr(" ");
        mx_printstr(files[i]->uid_name);
        mx_printstr("  ");
        mx_printstr(files[i]->gid_name);
        mx_printstr("  ");
        mx_until_print_format_str(mx_itoa((int)files[i]->size), 'r', ' ', max_size_len);
        mx_printstr(" ");
        mx_printstr(time_str);
        mx_printstr(" ");
        mx_printstr(files[i]->print_name);
        mx_printstr("\n");
    }
    opt = NULL;
}
