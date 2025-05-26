#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>


int copy_file(const char *src, const char *dest);

int copy_dir(const char *src, const char *dest);
