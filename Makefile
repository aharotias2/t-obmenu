OBMENU_OBJ = utf8utils.o htmlutils.o fileutils.o strlistutils.o obmenu.o 
STRARRAYTEST_OBJ = strarraytest.o strarrayutils.o
STRLISTTEST_OBJ = strlisttest.o strlistutils.o
FILETEST_OBJ = filetest.o fileutils.o strlistutils.o utf8utils.o
UTF8TEST_OBJ = utf8test.o utf8utils.o

CFLAGS = -Wall -pedantic -std=c99 -g -O0
CC = gcc

.SUFFIXES: .o .c

.c.o:
	$(CC) $(CFLAGS) -c $<

t-obmenu: $(OBMENU_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

strarraytest: $(STRARRAYTEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

strlisttest: $(STRLISTTEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

filetest: $(FILETEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

utf8test: $(UTF8TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

install:
	cp t-obmenu $(DESTDIR)

.PHONY: clean
clean:
	rm -f *.o strlisttest strarraytest c-obmenu


