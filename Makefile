### ln -s ../Makefile Makefile
CC= clang
CFLAGS = -ferror-limit=1 -g -O0 -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-const-variable -Wshadow
LDFLAGS = -L/usr/local/opt
LDLIBS = -lgcrypt -lcs50 -lm

EXE = foo

SRCS = foo.c bar.c
OBJS = $(SRCS:.c=.o)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)
