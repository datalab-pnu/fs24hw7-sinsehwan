CC=g++
CFLAGS= -Wall 
OBJS = testLedgerMain.o
INCDIR=./include
LIBDIR=./lib
DIRS = buf coseq str strlistp var student_reg 
#DIRS = buf coseq str strlistp var ledger ledgepost
#DIRS = buf fixed index recording var
MKDIR_P = mkdir -p

.PHONY: all clean mklibdir

all: mklibdir testLedgerMain

%.o: %.cpp
	$(CC) -c -I$(INCDIR) $(CFLAGS) -o $@ $<

mklibdir: $(LIBDIR)
$(LIBDIR):
	$(MKDIR_P) $(LIBDIR)

testLedgerMain: $(OBJS)
	@for d in $(DIRS); \
	do \
		$(MAKE) -C $$d; \
	done
	$(CC) -o testLedgerMain $(OBJS) -L$(LIBDIR) -lmyledger -lmybuffer -lmycoseq -lmystring -lmystrlistp -lmyvar -Wl,-rpath=$(LIBDIR)
	#$(CC) -o testLedgerMain $(OBJS) -L$(LIBDIR) -lmybuffer -lmycoseq -lmystring -lmystrlistp -lmyvar -lmyledger -lmyledgepost -Wl,-rpath=$(LIBDIR)
	#$(CC) -o testIdxFile $(OBJS) -L$(LIBDIR) -lmybuffer -lmyfixed -lmyindex -lmyrecording -lmyvar -Wl,-rpath=$(LIBDIR)
	#export LD_LIBRARY_PATH=$(LIBDIR)

clean:
	@for d in $(DIRS); \
	do \
		$(MAKE) -C $$d clean; \
	done
	-rm -rf testLedgerMain $(OBJS) $(LIBDIR)
