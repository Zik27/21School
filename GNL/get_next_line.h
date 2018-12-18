//
// Created by Virgie Urrigon greyjoy on 2018-12-18.
//

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 32
#include <unistd.h>
int get_next_line(const int fd, char **line);
#endif //GNL_GET_NEXT_LINE_H
