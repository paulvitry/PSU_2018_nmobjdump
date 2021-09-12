##
## EPITECH PROJECT, 2017
## Makefile
## File description:
##
##

SRCNM	=	src/nm/nm.c\
			src/nm/check_file.c\
			src/nm/manage_arg.c\
			src/nm/sort.c\
			src/nm/utils.c\
			src/nm/utils2.c\

SRCDUMP	=	src/objdump/objdump.c\
			src/objdump/check_file.c\
			src/objdump/manage_arg.c\
			src/objdump/print.c\
			src/objdump/flags.c\


OBJNM	=	$(SRCNM:.c=.o)

OBJDUMP	=	$(SRCDUMP:.c=.o)

NAMENM	=	my_nm

NAMEDUMP	=	my_objdump

CFLAGS	=	-W -Wall -Wextra -Werror -g3  -I./include -lm

nm: $(NAMENM) clean

$(NAMENM) :	$(OBJNM)
	g++ -o $(NAMENM) $(OBJNM) $(CFLAGS)

objdump: $(NAMEDUMP) clean

$(NAMEDUMP) :	$(OBJDUMP)
	g++ -o $(NAMEDUMP) $(OBJDUMP) $(CFLAGS)

clean:
	rm -f *.o
	rm -f src/nm/*.o
	rm -f src/objdump/*.o

fclean: clean
	rm -f $(NAMENM)
	rm -f $(NAMEDUMP)
	rm -f *#

re: clean all
