CC=		gcc
AR=		ar
CFLAGS=		-std=gnu99 -Wall -g
LDFLAGS=	
ARFLAGS=	rcs
COMPILER=	acc
LIBRARY=	libaddr.a

all:	$(LIBRARY) $(COMPILER)

%.o:		%.c
	$(CC) $(CFLAGS) -c -o $@ $^

$(LIBRARY):	lexer.o token.o utils.o
	$(AR) $(ARFLAGS) $@ $^

$(COMPILER):	acc.o $(LIBRARY)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(COMPILER) $(LIBRARY) *.o
