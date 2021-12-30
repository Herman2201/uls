#ifndef ULS
#define ULS
// #define _DEFAULT_SOURCE

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <uuid/uuid.h>
#include <sys/xattr.h>
#include <sys/ioctl.h>
#include <sys/acl.h>
#include <sys/errno.h>
#include <pwd.h>
#include <grp.h>
#include "libmx.h"

#define LEN_TAB 8
#define GET_STAT 1
#define GET_LSTAT 2

#define LS_HIDDEN_NOT 0
#define LS_HIDDEN_a 1
#define LS_HIDDEN_A 2

typedef struct s_ls {
    char *name;              //full file name, example ./src/main.c
    char *print_name;        //short file name, example main.c
    char *acl_inf;           //needed for flag l (additional information)
    char type;               //file type
    unsigned short int mode; //needed for flag l, from it we get permissions and file type
    long long int size;      //size in bytes
    unsigned int nlink;      //number of file links needed for flag l
    char *uid_name;          //user name
    char *gid_name;          //group name
    int blksize;             //number of occupied blocks (in bytes)
    long long int blocks;    //number of occupied blocks (in blocks)
    long int atime;          //last access time
    long int mtime;          //last change time
    long int ctime;          //last change of access rights
} t_ls;

typedef struct s_main {
    char **files;
    char *flags;
    char **error_dir;
    char **dir;
    int count_file_err;
} t_main;

void mx_ls_print_big_c(char **files, int file_n, int max_len, int len_terminal);
t_ls *mx_get_lstat(const char *file);
int mx_until_get_size_arr(char **str_arr);
t_ls **mx_ls_create_struct_arr(int files_number);
void mx_create_ls(t_main *main);
bool mx_is_l_flag(char *flags, char flag);
int mx_get_char_index(const char *str, char c);
char *mx_ls_get_print_name(const char *file);
char *mx_ls_get_acl_inf(const char *file);
char mx_ls_get_type(unsigned short int file_mode);
char *mx_ls_get_uid_name(int st_uid);
char *mx_ls_get_gid_name(int st_gid);
void mx_ls_loop(int i_total, char **files_name, char *flags, t_main *main);
void mx_ls_print(int i_total, t_ls **files, int file_n, char *flags);
void mx_ls_print_l(int i_total, t_ls **files, int file_n, char *opt);
int mx_untill_get_max_nlink(t_ls **files);
int mx_untill_get_max_size(t_ls **files);
void mx_until_print_format_str(char *str, char location, char symbol, int size);
char **mx_read_dir(char *dir, int headen);
int mx_files_in_dir(char *dir, int headen);
char **mx_create_param_dir(char **argv, int argc);
char **mx_create_param_err_dir(char **argv, int argc);
int mx_count_err_dir(char **argv, int argc);






bool flagError(int argc, char *argv[], bool *estLflag);
t_list *getFoldsList(int argc, char **argv);
void foldsNULL(t_list *foldy);
bool openFolder(char *foldToOpen, bool b);
bool vyvodFolds(t_list *foldy, bool b);
char *formListNaVyvod2(char *path, int *countGovna);
void vyvodColonok(t_list *list);
void vyvodColonok2(t_list *list);
void vyvodFlagL(char *fold, t_list *list);
char *processPermitions(mode_t perm);
char *formDateTime(time_t vremya);
int arrayMaxLength(char ***str_arr, int index, int size);
void print_spaces(char *str, int maxLen);
char **mx_create_param_arr(char **argv, int argc);
char **mx_until_create_char_arr(int number);
char *mx_create_flags_str(char **argv, int argc);

#endif /* ULS */
