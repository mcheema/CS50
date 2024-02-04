### ln -s ../Makefile Makefile
CC= clang
CFLAGS = -ferror-limit=1 -gdwarf-4 -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wshadow
LDLIBS = -lcrypt -lcs50 -lm

EXE = foo

SRCS = foo.c bar.c
OBJS = $(SRCS:.c=.o)


$(EXE): $(OBJS)
     $(CC) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS)
