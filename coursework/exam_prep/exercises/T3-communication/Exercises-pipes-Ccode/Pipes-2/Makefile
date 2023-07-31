CC	= gcc
LD	= gcc

CFLAGS	= -g -Wall
CFLAGS	+= -I. 
LDFLAGS	= 

OBJS	= 

LIBS	= #-lpthread

SRCS	= $(patsubst %.o,%.c,$(OBJS))

PRGS	=  oneprocesspipe fatherchildpipe childrenpipe redirpipe 
all: $(PRGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $*.c $(INCLUDE) -o $@

$(PRGS): $(OBJS)
$(PRGS): $(LIBS)
$(PRGS): % : %.o
	$(CC) $(CFLAGS) -o $@ $< $(OBJS) $(LDFLAGS) $(LIBS)

clean:
	-rm -f *.o  *~ $(PRGS)

