#include "uls.h"

int static mx_until_get_len_number(unsigned long long int number) {
    int len = 0;

    for (unsigned long long int i = number; i != 0; i /= 10)
        len++;
    return len;
}

int mx_untill_get_max_nlink(t_ls **files)
{
    unsigned int max_nlink = 0;

    for (int i = 0; files[i]; i++)
        if (files[i]->nlink > max_nlink)
            max_nlink = files[i]->nlink;
    return mx_until_get_len_number(max_nlink);
}
