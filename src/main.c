#include "uls.h"

void static error_flags(int argc, char *argv[])
{
    for (int i = 1; i < argc && argv[i][0] == '-'; i++)
    {
        for (int j = 1; j < mx_strlen(argv[i]); j++)
        {
            if (argv[i][j] != 'l')
            {
                mx_printerr("uls: illegal option -- ");
                write(STDERR_FILENO, &argv[i][j], 1);
                mx_printerr("\nusage: uls [-l] [file ...]\n");
                exit(0);
            }
        }
    }
}

t_main *mx_create_main(int argc, char *argv[])
{
    t_main *main = malloc(sizeof(t_main));

    main->files = mx_create_param_arr(argv, argc);
    main->flags = mx_create_flags_str(argv, argc);
    return main;
}

int main(int argc, char *argv[])
{
    t_main *main = NULL;
    main = mx_create_main(argc, argv);
    error_flags(argc, argv);
    mx_create_ls(main);
    return 0;
}
