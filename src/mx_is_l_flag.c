#include "uls.h"

bool mx_is_l_flag(char *flags, char flag)
{
    if (mx_get_char_index(flags, flag) >= 0)
    {
        return true;
    }
    return false;
}
