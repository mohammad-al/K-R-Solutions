#ifndef LINES_H
#define LINES_H

int readlines(char *lineptr[], int maxlines, char*line_storage, int maxstorage);
void writelines(char *lineptr[], int nlines);
int my_getline(char line[], int limit);

#endif
