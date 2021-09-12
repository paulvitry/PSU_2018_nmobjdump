/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** check_file
*/

#include "objdump.h"

bool    isDir(char *file)
{
    if (opendir(file) == NULL) {
        return false;
    }
    return true;

}

bool    fileGood(char *filename)
{
    Elf64_Ehdr header;

    FILE* file = fopen(filename, "rb");
    if (file) {
        fread(&header, 1, sizeof(header), file);
        if (memcmp(header.e_ident, ELFMAG, SELFMAG) == 0) {
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}

bool    fileExist(char *file)
{
    int fd;
    bool valid = true;

    fd = open(file, O_RDONLY);
    if (fd == -1)
        valid = false;
    return valid;
}