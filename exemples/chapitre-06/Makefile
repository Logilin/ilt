
APPLICATIONS =                 \
	exemple-01             \
	exemple-02             \
	exemple-03             \
	exemple-04             \

XENOCONFIG=/usr/xenomai/bin/xeno-config

CC=$(shell      $(XENOCONFIG) --cc)
MY_CFLAGS=-g
CFLAGS=$(shell  $(XENOCONFIG) --skin=native --cflags)  $(MY_CFLAGS)
LDFLAGS=$(shell $(XENOCONFIG) --skin=native --ldflags) $(MY_LDFLAGS)
LIBDIR=$(shell  $(XENOCONFIG) --skin=native --libdir)  $(MY_LIBDIR)
LDFLAGS+=-lnative 
LDLIBS=-lnative -lxenomai

all:: $(APPLICATIONS)

clean::
	$(RM) -f $(APPLICATIONS) *.o *~
