#include "uls.h"

int static mx_until_get_len_number(unsigned long long int number)
{
    int len = 0;

    for (unsigned long long int i = number; i != 0; i /= 10)
        len++;
    return len;
}

int mx_untill_get_max_size(t_ls **files)
{
    long long int max_size = 0;

    for (int i = 0; files[i]; i++)
        if (files[i]->size > max_size)
            max_size = files[i]->size;
    return mx_until_get_len_number(max_size);
}
