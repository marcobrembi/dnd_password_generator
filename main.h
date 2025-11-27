#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifdef _WIN32
#include <process.h>
#define GETPID _getpid
#else
#include <unistd.h>
#define GETPID getpid
#endif

int get_file_noise();
void d4(int *order, FILE *fp);
void d8(char *speciali, FILE *fp);
void d10(char *numbers, FILE *fp);
void d20_d12_d6(unsigned char *ascii, FILE *fp);
