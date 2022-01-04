#include "uls.h"

void mx_sort_args(int argc, int start, char **argv, int flags) {
    char *tmp = NULL;

    if (!start)
        start++;
    if (MX_F_ISFL(flags)) {
        return;
    }
    for (int i = start + 1; i < argc; i++) {
        for (int j = i - 1; j < argc - 1; j++) {
            if (mx_strcmp(argv[j], argv[j + 1]) > 0) {
                tmp = argv[j];
                argv[j] = argv[j + 1];
                argv[j + 1] = tmp;
            }
        }
    }
}
