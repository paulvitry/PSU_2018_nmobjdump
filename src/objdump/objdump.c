/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** objdump
*/

#include "objdump.h"

void    printSectionContent(int counter, elf_t elf)
{
    int addr = elf.shdr[counter].sh_addr;
    unsigned int plus = 0;
    unsigned char *w = (unsigned char *)
                        ((char *)elf.elf + elf.shdr[counter].sh_offset);
    int z = 0;

    while (plus < elf.shdr[counter].sh_size)
    {
        if (plus % 16 == 0)
            printf(" %04x ", addr);
        printf("%02x", w[plus++]);
        if (plus % 4 == 0 && plus % 16 && plus < elf.shdr[counter].sh_size)
            printf(" ");
        if (plus % 16 == 0)
            addr += 16;
        if (plus % 16 == 0 || plus >= elf.shdr[counter].sh_size)
            print_ascii(plus, &z, w);
    }
}

void    print_header(elf_t elf, char *filename)
{
    flags_t flags = get_flags(elf);
    
    printf("\n%s:     file format %s\n", filename, "elf64-x86-64");
    printf("architecture: i386:x86-64, flags 0x%08d:\n", get_flags_sum(flags));
    print_flags(flags);
    printf("start address 0x%016x\n\n", (int)elf.elf->e_entry);
}

void    printSection(elf_t elf, char *filename)
{
    int counter = 1;

    elf.elf = elf.buf;
    elf.shdr = (Elf64_Shdr *) (elf.buf + elf.elf->e_shoff);
    elf.strtab = (char *) (elf.buf + elf.shdr[elf.elf->e_shstrndx].sh_offset);
    print_header(elf, filename);
    while (counter < elf.elf->e_shnum) {
        if (elf.shdr[counter].sh_flags != 0
            && strcmp(".bss", &elf.strtab[elf.shdr[counter].sh_name]) != 0) {
            printf("Contents of section %s:\n",
                                    &elf.strtab[elf.shdr[counter].sh_name]);
            printSectionContent(counter, elf);
        }
        counter++;
    }
}

int    objdump(char *filename)
{
    elf_t   elf;

    elf.fd = open(filename, O_RDONLY);
    if (elf.fd !=  -1)
    {
        fstat(elf.fd, &elf.s);
        elf.buf = mmap(NULL, elf.s.st_size, PROT_READ, MAP_PRIVATE, elf.fd, 0);
        if (elf.buf != NULL) {
            printSection(elf, filename);
        }
        close(elf.fd);
        return 0;
    }
    return 1;
}

int main(int ac, char **av)
{
    int to_return = 0;

    if (ac == 1) {
        to_return = noArg(to_return);
    } else if (ac > 2) {
        to_return = sevralArg(to_return, av);
    } else {
        to_return = oneArg(to_return, av);
    }
    return to_return;
}