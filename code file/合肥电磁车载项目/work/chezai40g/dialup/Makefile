CROSS_COMPILE = arm-a5vfpv4-linux-gnueabi-
CC = $(CROSS_COMPILE)gcc
STRIP = $(CROSS_COMPILE)strip

CFLAGS += -Wall
LIBS += -pthread

PROCS = dialupd dialcli

all: $(PROCS)

dialupd: dialupd.c
	$(CC) $^ -o $@ $(CFLAGS) $(LIBS)
	$(STRIP) $@
dialcli: dialcli.c
	$(CC) $^ -o $@ $(CFLAGS) $(LIBS)
	$(STRIP) $@

.PHONY: clean
clean:
	rm -f $(PROCS)
