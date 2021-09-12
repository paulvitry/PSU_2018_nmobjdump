/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** nm
*/

#include "nm.h"

void    *getBuffer(const char *filename)
{
    int           fd;
    void          *buf;
    struct        stat s;

    fd = open(filename, O_RDONLY);
    if (fd !=  -1)
    {
        fstat(fd, &s);
        buf = mmap(NULL , s.st_size , PROT_READ , MAP_PRIVATE , fd, 0);
        if (buf != NULL) {
            close(fd);
            return buf;
        }
        else
            perror("mmap");
        close(fd);
    }
    return NULL;
}

char    print_type(Elf64_Sym sym, Elf64_Shdr *shdr)
{
    char  c;

    if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
        c = 'u';
    else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK) {
        c = 'W';
        if (sym.st_shndx == SHN_UNDEF)
            c = 'w';
    } else if (ELF64_ST_BIND(sym.st_info) ==
        STB_WEAK && ELF64_ST_TYPE(sym.st_info) == STT_OBJECT) {
        c = 'V';
        if (sym.st_shndx == SHN_UNDEF)
            c = 'v';
    } else if (sym.st_shndx == SHN_UNDEF)
        c = 'U';
    else if (sym.st_shndx == SHN_ABS)
        c = 'A';
    else if (sym.st_shndx == SHN_COMMON)
        c = 'C';
    else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
        && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'B';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
        && shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
        c = 'R';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
        && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'D';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
        && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        c = 'T';
    else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
        c = 'D';
    else if (shdr[sym.st_shndx].sh_type == 17)
        c = 'n';
    else
        c = 't';
    if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != 't' && c != 'n')
        c += 32;
    return c;
}

void    nm(const char *filename)
{
    void *buf = getBuffer(filename);
    elf_t elf;
    int entries;

    elf.strtab = NULL;
    if (buf == NULL)
        return;
    elf.elf = buf;
    elf.sections = (Elf64_Shdr *)((char *)buf + elf.elf->e_shoff);
    elf.str = (char *) (buf + elf.sections[elf.elf->e_shstrndx].sh_offset);
    for (int i = 0; i < elf.elf->e_shnum; i++) {
        if (elf.sections[i].sh_type == SHT_SYMTAB) {
            elf.symtab = (Elf64_Sym *)((char *)buf + elf.sections[i].sh_offset);
            entries = elf.sections[i].sh_size / elf.sections[i].sh_entsize;
        }
        if (strcmp(&elf.str[elf.sections[i].sh_name], ".strtab") == 0)
            elf.strtab = (Elf64_Shdr *) &elf.sections[i];
    }
    if (elf.strtab != NULL) {
        elf.str = (char *) (buf + elf.strtab->sh_offset);
        print_nm(elf, entries);
    } else {
        fprintf(stderr, "nm: %s: no symbols\n", filename);
    }
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