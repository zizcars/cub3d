
#ifndef PARSING_H
#define PARSING_H

#include "types.h"
//              check.c
bool check_filename(char *file_name);
// bool check_char(char c);
bool check_color(int *color);
void check_map(t_info *info);

//			array
int array_length(char **array);
void free_array(char ***array);
int array_size(char **array);
char **append_array(char **old_array, char *arg);

t_info *read_info(int fd);
void ft_error(char *error_ms);
// bool check_map(char *row);

#endif
