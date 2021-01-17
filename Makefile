
# Makefile for CMPSC311 - Assign #1

# Variables
CC=gcc
LINK=gcc
CFLAGS=-c -g -Wall -I.
LINKFLAGS=-L. -g 
LINKLIBS=-lcmpsc311 -lgcrypt -lcurl

# Productions
.SUFFIXES: .o .c

.c.o:
	$(CC) $(CFLAGS) -o $@ $<

assign1-cmpsc311-f20 : assign1-cmpsc311-f20.o
	$(LINK) $(LINKFLAGS) assign1-cmpsc311-f20.o $(LINKLIBS) -o $@

clean : 
	rm -f assign1-cmpsc311-f20.o assign1-cmpsc311-f20
