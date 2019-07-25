CC = gcc
CFLAGS = -g -O2
LIBS = -lcrypto -lssl -lz 
INSTALL=/bin/install -c
prefix=/usr/local
bindir=$(prefix)${exec_prefix}/bin
DESTDIR=
FLAGS=$(CFLAGS) -DPACKAGE_NAME=\"\" -DPACKAGE_TARNAME=\"\" -DPACKAGE_VERSION=\"\" -DPACKAGE_STRING=\"\" -DPACKAGE_BUGREPORT=\"\" -DPACKAGE_URL=\"\" -DSTDC_HEADERS=1 -DHAVE_LIBZ=1 -D_LARGEFILE64_SOURCE=1 -D_FILE_OFFSET_BITS=64 -DHAVE_LIBSSL=1 -DHAVE_LIBCRYPTO=1 
OBJ=common.o settings.o containerfiles.o outputfiles.o servicetypes.o extract_text.o download.o display.o players.o selectformat.o ehow.o youtube.o 

all: $(OBJ)
	@cd libUseful; $(MAKE)
	$(CC) $(FLAGS) -o movgrab main.c $(OBJ) libUseful/libUseful.a $(LIBS) 

clean:
	@rm -f movgrab *.o libUseful/*.o libUseful/*.a libUseful/*.so config.log config.status

common.o: common.c common.h
	$(CC) $(FLAGS) -c common.c

settings.o: settings.c settings.h
	$(CC) $(FLAGS) -c settings.c

containerfiles.o: containerfiles.c containerfiles.h
	$(CC) $(FLAGS) -c containerfiles.c

outputfiles.o: outputfiles.c outputfiles.h
	$(CC) $(FLAGS) -c outputfiles.c

ehow.o: ehow.c ehow.h
	$(CC) $(FLAGS) -c ehow.c

youtube.o: youtube.c youtube.h
	$(CC) $(FLAGS) -c youtube.c

servicetypes.o: servicetypes.c servicetypes.h
	$(CC) $(FLAGS) -c servicetypes.c

download.o: download.c download.h
	$(CC) $(FLAGS) -c download.c

display.o: display.c display.h
	$(CC) $(FLAGS) -c display.c

players.o: players.c players.h
	$(CC) $(FLAGS) -c players.c

selectformat.o: selectformat.c selectformat.h
	$(CC) $(FLAGS) -c selectformat.c

extract_text.o: extract_text.c extract_text.h
	$(CC) $(FLAGS) -c extract_text.c


install:
	$(INSTALL) -d $(DESTDIR)$(bindir)
	$(INSTALL) movgrab $(DESTDIR)$(bindir)

test:
	echo "no tests"
