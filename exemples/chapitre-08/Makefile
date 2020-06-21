##############################################################################
## Exemple de la formation "Temps-reel Linux et Xenomai"
##
## Christophe Blaess 2010-2020
## http://christophe.blaess.fr
## Licence GPLv2
##############################################################################

EXE =                    \
  example-01             \
  example-02             \
  example-03             \
  example-04             \
  example-05             \

XENOCONFIG=/usr/xenomai/bin/xeno-config

CC=$(shell      $(XENOCONFIG) --cc)
MY_CFLAGS=-g
CFLAGS=$(shell  $(XENOCONFIG) --alchemy --cflags)  $(MY_CFLAGS)
LDFLAGS=$(shell $(XENOCONFIG) --alchemy --ldflags) $(MY_LDFLAGS)
LIBDIR=$(shell  $(XENOCONFIG) --alchemy --libdir)  $(MY_LIBDIR)

all:: $(EXE)

clean::
	$(RM) -f $(EXE) *.o *~
