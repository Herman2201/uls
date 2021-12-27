#include "uls.h"

void static mx_ls_sort_default(t_ls **arr) {
    t_ls *temp;
    int size = mx_until_get_size_arr((char **)arr);

    for (int i = 0; i < size; ++i) {
        for (int j = i; j < size; ++j) {
            if (mx_strcmp(arr[i]->name, arr[j]->name) > 0) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void mx_ls_loop(char **files_name, char *flags, t_main *main)
{
    int file_n = mx_until_get_size_arr(files_name);
    t_ls **files = mx_ls_create_struct_arr(file_n); //массив структур файлов

    for (int i = 0; files_name[i]; i++)
        files[i] = mx_get_lstat(files_name[i]); //заполнение массива структурами

    //здесь нужно вставить функцию сортировки
    mx_ls_sort_default(files);
    mx_ls_print(files, file_n, flags); //печать файлов
    main = NULL;
}
